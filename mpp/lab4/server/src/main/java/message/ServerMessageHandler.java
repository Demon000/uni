package message;

import domain.Arbiter;
import domain.Score;
import service.IService;
import utils.ServiceError;

import java.io.IOException;
import java.net.Socket;
import java.util.List;

public class ServerMessageHandler extends MessageHandler {
    private final IService service;
    private Arbiter arbiter;

    public ServerMessageHandler(Socket socket, IService service) throws IOException {
        super(socket);

        this.service = service;
    }

    @Override
    public void onReceive(Object object) {
        Message message = (Message) object;

        switch (message.type) {
            case LOGIN_REQUEST:
                onLoginRequest((LoginData) message.data);
                break;
            case PARTICIPANT_SCORES_REQUEST:
                onParticipantScoresRequest();
                break;
            case RANKING_SCORES_REQUEST:
                onRankingScoresRequest();
                break;
            case SET_SCORE_REQUEST:
                onSetScoreRequest((ScoreSetData) message.data);
                break;
        }
    }

    public void onLoginRequest(LoginData data) {
        try {
            Arbiter arbiter = service.loginArbiter(data.getName(), data.getPassword());
            this.arbiter = arbiter;
            send(MessageType.LOGIN_RESPONSE, arbiter);
        } catch (ServiceError e) {
            send(MessageType.LOGIN_REQUEST_ERROR, e.getCause().getMessage());
        }
    }

    public void onParticipantScoresRequest() {
        try {
            List<Score> scores = service.getScores();
            send(MessageType.PARTICIPANT_SCORES_RESPONSE, scores);
        } catch (ServiceError e) {
            send(MessageType.PARTICIPANT_SCORES_REQUEST_ERROR, e.getCause().getMessage());
        }
    }

    public void onRankingScoresRequest() {
        try {
            List<Score> scores = service.getScoresForType(arbiter.getType());
            send(MessageType.RANKING_SCORES_RESPONSE, scores);
        } catch (ServiceError e) {
            send(MessageType.RANKING_SCORES_REQUEST_ERROR, e.getCause().getMessage());
        }
    }

    public void onSetScoreRequest(ScoreSetData data) {
        try {
            Score score = service.setScoreValue(data.getParticipantId(), arbiter.getType(), data.getValue());
            send(MessageType.SET_SCORE_RESPONSE, score);
        } catch (ServiceError e) {
            send(MessageType.SET_SCORE_REQUEST_ERROR, e.getCause().getMessage());
        }
    }

    public void onSetScore(Score score) {
        send(MessageType.SET_SCORE_BROADCAST, score);
    }
}
