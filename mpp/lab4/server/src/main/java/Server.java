import domain.Arbiter;
import domain.Score;
import message.LoginData;
import message.ScoreSetData;
import message.ServerMessageHandler;
import message.ServerMessageReceiver;
import repository.RepositoryError;
import service.Service;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Server implements ServerMessageReceiver {
    private final List<ServerMessageHandler> messageHandlers = new ArrayList<>();
    private Thread clientConnectionThread;
    private Service service;
    private ServerSocket serverSocket;

    public Server(Service service, int port) throws IOException {
        this.service = service;
        this.serverSocket = new ServerSocket(port);

        this.clientConnectionThread = new Thread(() -> {
            System.out.println("Connection: started running connection thread");
            while (!Thread.interrupted()) {
                try {
                    System.out.println("Connection: waiting for client connection");
                    Socket clientSocket = serverSocket.accept();
                    System.out.println("Connection: client connected!");
                    ServerMessageHandler messageHandler = new ServerMessageHandler(clientSocket);
                    synchronized (messageHandlers) {
                        messageHandlers.add(messageHandler);
                    }
                    messageHandler.addReceiver(this);
                    messageHandler.start();
                } catch (IOException e) {
                    return;
                }
            }
        }, "ClientConnection");
    }

    public void start() {
        clientConnectionThread.start();
    }

    public void stop() throws IOException {
        clientConnectionThread.interrupt();
        serverSocket.close();
    }

    public void broadcastScoreSet(Score score) {
        synchronized (messageHandlers) {
            for (ServerMessageHandler messageHandler : messageHandlers) {
                messageHandler.broadcastSetScore(score);
            }
        }
    }

    @Override
    public void onLoginRequest(ServerMessageHandler messageHandler, LoginData data) {
        try {
            Arbiter arbiter = service.loginArbiter(data.getName(), data.getPassword());
            messageHandler.respondLogin(arbiter);
        } catch (RepositoryError e) {
            messageHandler.respondLoginError(e.getMessage());
        }
    }

    @Override
    public void onParticipantScoresRequest(ServerMessageHandler messageHandler) {
        try {
            List<Score> scores = service.getScores();
            messageHandler.respondParticipantScores(scores);
        } catch (RepositoryError e) {
            messageHandler.respondParticipantScoresError(e.getMessage());
        }
    }

    @Override
    public void onRankingScoresRequest(ServerMessageHandler messageHandler) {
        try {
            List<Score> scores = service.getScoresForType(messageHandler.getArbiter().getType());
            messageHandler.respondRankingScores(scores);
        } catch (RepositoryError e) {
            messageHandler.respondRankingScoresError(e.getMessage());
        }
    }

    @Override
    public void onSetScoreRequest(ServerMessageHandler messageHandler, ScoreSetData data) {
        try {
            Score score = service.setScoreValue(data.getParticipantId(),
                    messageHandler.getArbiter().getType(), data.getValue());
            broadcastScoreSet(score);
        } catch (RepositoryError e) {
            messageHandler.respondSetScoreError(e.getMessage());
        }
    }
}
