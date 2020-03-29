package message;

import domain.Arbiter;
import domain.Score;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ClientMessageHandler extends MessageHandler {
    public ClientMessageHandler(Socket socket) throws IOException {
        super(socket);
    }

    public void addReceiver(ClientMessageReceiver receiver) {
        super.addReceiver(receiver);
    }

    public void removeReceiver(ClientMessageReceiver receiver) {
        super.removeReceiver(receiver);
    }

    public static ClientMessageHandler createForAddress(String serverAddress, Integer serverPort) throws IOException {
        Socket socket = new Socket(serverAddress, serverPort);
        return new ClientMessageHandler(socket);
    }

    @Override
    protected void objectReceived(Object object) {
        Message message = (Message) object;

        receivers.forEach(receiver -> {
            ClientMessageReceiver messageReceiver = (ClientMessageReceiver) receiver;
            List<Score> scores;
            String error;

            switch (message.type) {
                case LOGIN_REQUEST_ERROR:
                    error = (String) message.data;
                    messageReceiver.onLoginRequestError(error);
                    break;
                case LOGIN_RESPONSE:
                    Arbiter arbiter = (Arbiter) message.data;
                    messageReceiver.onLoginResponse(arbiter);
                    break;
                case PARTICIPANT_SCORES_REQUEST_ERROR:
                    error = (String) message.data;
                    messageReceiver.onParticipantScoresRequestError(error);
                    break;
                case PARTICIPANT_SCORES_RESPONSE:
                    scores = (List<Score>) message.data;
                    messageReceiver.onParticipantScoresResponse(scores);
                    break;
                case RANKING_SCORES_REQUEST_ERROR:
                    error = (String) message.data;
                    messageReceiver.onRankingScoresRequestError(error);
                    break;
                case RANKING_SCORES_RESPONSE:
                    scores = (List<Score>) message.data;
                    messageReceiver.onRankingScoresResponse(scores);
                    break;
                case SET_SCORE_REQUEST_ERROR:
                    error = (String) message.data;
                    messageReceiver.onSetScoreRequestError(error);
                    break;
                case SET_SCORE_BROADCAST:
                    Score score = (Score) message.data;
                    messageReceiver.onSetScoreBroadcast(score);
                    break;
            }
        });

        super.objectReceived(object);
    }

    public void requestLogin(LoginData data) {
        send(MessageType.LOGIN_REQUEST, data);
    }

    public void requestParticipantScores() {
        send(MessageType.PARTICIPANT_SCORES_REQUEST);
    }

    public void requestRankingScores() {
        send(MessageType.RANKING_SCORES_REQUEST);
    }

    public void requestSetScore(ScoreSetData data) {
        send(MessageType.SET_SCORE_REQUEST, data);
    }
}
