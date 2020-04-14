package message;

import domain.Arbiter;
import domain.Score;
import service.IService;
import service.IServiceObserver;
import service.ServiceError;

import java.io.IOException;
import java.net.Socket;
import java.rmi.RemoteException;
import java.util.List;

public class ServerMessageHandler extends MessageHandler implements IServiceObserver {
    private final IService service;
    private Arbiter arbiter;

    public ServerMessageHandler(Socket socket, IService service) throws IOException {
        super(socket);

        this.service = service;
        this.service.addObserver(this);
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
        } catch (ServiceError | RemoteException e) {
            send(MessageType.LOGIN_REQUEST_ERROR, e.getMessage());
        }
    }

    public void onParticipantScoresRequest() {
        try {
            List<Score> scores = service.getScores();
            send(MessageType.PARTICIPANT_SCORES_RESPONSE, scores);
        } catch (ServiceError | RemoteException e) {
            send(MessageType.PARTICIPANT_SCORES_REQUEST_ERROR, e.getMessage());
        }
    }

    public void onRankingScoresRequest() {
        try {
            List<Score> scores = service.getScoresForType(arbiter.getType());
            send(MessageType.RANKING_SCORES_RESPONSE, scores);
        } catch (ServiceError | RemoteException e) {
            send(MessageType.RANKING_SCORES_REQUEST_ERROR, e.getMessage());
        }
    }

    public void onSetScoreRequest(ScoreSetData data) {
        try {
            Score score = service.setScoreValue(data.getParticipantId(), arbiter.getType(), data.getValue());
            send(MessageType.SET_SCORE_RESPONSE, score);
        } catch (ServiceError | RemoteException e) {
            send(MessageType.SET_SCORE_REQUEST_ERROR, e.getMessage());
        }
    }

    public void onSetScore(Score score) {
        send(MessageType.SET_SCORE_BROADCAST, score);
    }
}
