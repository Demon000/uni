import domain.Score;
import message.ServerMessageHandler;
import message.ServerMessageReceiver;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import service.IService;
import service.IServiceObserver;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Server implements IServiceObserver {
    protected final Logger logger = LogManager.getLogger();

    private final List<ServerMessageHandler> messageHandlers = new ArrayList<>();
    private final ServerSocket serverSocket;
    private final IService service;
    private ClientConnection clientConnectionThread;

    public Server(IService service, int port) throws IOException {
        this.service = service;
        this.serverSocket = new ServerSocket(port);

        this.service.addObserver(this);
    }

    private class ClientConnection extends Thread {
        public ClientConnection() {
            super("ClientConnection");
        }

        @Override
        public void run() {
            logger.info("started running connection thread");
            while (!Thread.interrupted()) {
                try {
                    logger.info("waiting for client connection");
                    Socket clientSocket = serverSocket.accept();
                    logger.info("client connected");
                    ServerMessageHandler messageHandler = new ServerMessageHandler(clientSocket, service);
                    synchronized (messageHandlers) {
                        messageHandlers.add(messageHandler);
                    }
                    messageHandler.start();
                } catch (IOException e) {
                    logger.error("thread interrupted");
                    return;
                }
            }
        }
    }

    public void start() {
        if (clientConnectionThread == null) {
            clientConnectionThread = new ClientConnection();
            clientConnectionThread.start();
        }
    }

    public void stop() throws IOException {
        if (clientConnectionThread != null) {
            clientConnectionThread.interrupt();
        }

        if (serverSocket.isBound()) {
            serverSocket.close();
        }
    }

    @Override
    public void onSetScore(Score score) {
        synchronized (messageHandlers) {
            messageHandlers.forEach(handler -> handler.onSetScore(score));
        }
    }
}
