package service;

import domain.Arbiter;
import domain.Score;
import domain.ScoreType;
import message.*;
import utils.ServiceError;

import java.io.IOException;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ClientMessageService extends BaseService implements IObjectReceiver {
    private final String serverAddress;
    private final Integer serverPort;

    private final BlockingQueue<Message> inboundMessages = new LinkedBlockingQueue<>();
    private MessageHandler handler;

    public ClientMessageService(String serverAddress, Integer serverPort) {
        this.serverAddress = serverAddress;
        this.serverPort = serverPort;
    }

    @Override
    public void onReceive(Object object) {
        Message message = (Message) object;

        switch (message.type) {
            case SET_SCORE_BROADCAST:
                Score score = (Score) message.data;
                System.out.println(score);
                observerSetScore(score);
                break;
            default:
                inboundMessages.add(message);
                break;
        }
    }

    public void stop() throws IOException {
        if (handler != null) {
            handler.stop();
        }
    }

    public void start() throws IOException {
        if (handler == null) {
            handler = MessageHandler.createForAddress(serverAddress, serverPort);
            handler.setReceiver(this);
            handler.start();
        }
    }

    private Object sendAndReceive(MessageType type, Object data,
                                 MessageType errorType, MessageType responseType) throws ServiceError {
        try {
            start();
        } catch (IOException e) {
            throw new ServiceError(e);
        }

        try {
            handler.send(type, data);
            Message response = inboundMessages.take();
            if (response.type == errorType) {
                String error = (String) response.data;
                throw new ServiceError(error);
            } else if (response.type == responseType) {
                return response.data;
            } else {
                throw new ServiceError("Response type is invalid");
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
            throw new ServiceError(e);
        }
    }

    private Object sendAndReceive(MessageType type, MessageType errorType,
                                 MessageType responseType) throws ServiceError {
        return sendAndReceive(type, null, errorType, responseType);
    }

    @Override
    public Arbiter loginArbiter(String name, String password) throws ServiceError {
        return (Arbiter) sendAndReceive(MessageType.LOGIN_REQUEST, new LoginData(name, password),
                MessageType.LOGIN_REQUEST_ERROR, MessageType.LOGIN_RESPONSE);
    }

    @Override
    public List<Score> getScores() throws ServiceError {
        return (List<Score>) sendAndReceive(MessageType.PARTICIPANT_SCORES_REQUEST,
                MessageType.PARTICIPANT_SCORES_REQUEST_ERROR, MessageType.PARTICIPANT_SCORES_RESPONSE);
    }

    @Override
    public List<Score> getScoresForType(ScoreType type) throws ServiceError {
        return (List<Score>) sendAndReceive(MessageType.RANKING_SCORES_REQUEST,
                MessageType.RANKING_SCORES_REQUEST_ERROR, MessageType.RANKING_SCORES_RESPONSE);
    }

    @Override
    public Score setScoreValue(int participantId, ScoreType type, int value) throws ServiceError {
        return (Score) sendAndReceive(MessageType.SET_SCORE_REQUEST, new ScoreSetData(participantId, value),
                MessageType.SET_SCORE_REQUEST_ERROR, MessageType.SET_SCORE_RESPONSE);
    }
}
