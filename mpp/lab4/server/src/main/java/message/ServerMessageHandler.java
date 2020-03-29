package message;

import domain.Arbiter;
import domain.Score;

import java.io.IOException;
import java.net.Socket;
import java.util.List;

public class ServerMessageHandler extends MessageHandler {
    private Arbiter arbiter;

    public ServerMessageHandler(Socket socket) throws IOException {
        super(socket);
    }

    public void addReceiver(ServerMessageReceiver receiver) {
        System.out.println("Adding receiver");
        super.addReceiver(receiver);
    }

    public void removeReceiver(ServerMessageReceiver receiver) {
        super.removeReceiver(receiver);
    }

    @Override
    protected void objectReceived(Object object) {
        Message message = (Message) object;
        
        receivers.forEach(receiver -> {
            ServerMessageReceiver messageReceiver = (ServerMessageReceiver) receiver;

            switch (message.type) {
                case LOGIN_REQUEST:
                    LoginData loginData = (LoginData) message.data;
                    messageReceiver.onLoginRequest(this, loginData);
                    break;
                case PARTICIPANT_SCORES_REQUEST:
                    messageReceiver.onParticipantScoresRequest(this);
                    break;
                case RANKING_SCORES_REQUEST:
                    messageReceiver.onRankingScoresRequest(this);
                    break;
                case SET_SCORE_REQUEST:
                    ScoreSetData scoreSetData = (ScoreSetData) message.data;
                    messageReceiver.onSetScoreRequest(this, scoreSetData);
                    break;
            }
        });

        super.objectReceived(object);
    }

    public Arbiter getArbiter() {
        return arbiter;
    }

    public void respondLoginError(String message) {
        send(MessageType.LOGIN_REQUEST_ERROR, message);
    }

    public void respondLogin(Arbiter arbiter) {
        this.arbiter = arbiter;
        send(MessageType.LOGIN_RESPONSE, arbiter);
    }

    public void respondParticipantScoresError(String message) {
        send(MessageType.PARTICIPANT_SCORES_REQUEST_ERROR, message);
    }

    public void respondParticipantScores(List<Score> scores) {
        send(MessageType.PARTICIPANT_SCORES_RESPONSE, scores);
    }

    public void respondRankingScoresError(String message) {
        send(MessageType.PARTICIPANT_SCORES_REQUEST_ERROR, message);
    }

    public void respondRankingScores(List<Score> scores) {
        send(MessageType.RANKING_SCORES_RESPONSE, scores);
    }

    public void respondSetScoreError(String message) {
        send(MessageType.SET_SCORE_REQUEST_ERROR, message);
    }

    public void broadcastSetScore(Score score) {
        send(MessageType.SET_SCORE_BROADCAST, score);
    }
}
