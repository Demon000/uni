package service;

import domain.Arbiter;
import domain.Score;
import grpc.triathlon.*;
import grpc.triathlon.TriathlonServiceGrpc.TriathlonServiceBlockingStub;
import grpc.triathlon.TriathlonServiceGrpc.TriathlonServiceStub;
import io.grpc.*;
import utils.GrpcHeaderCopy;

import java.util.*;

public class GrpcService extends Observable implements IService {
    public static String LOGIN_EVENT = "LOGIN_EVENT";
    private final String serverAddress;
    private final Integer serverPort;

    private final GrpcHeaderCopy authorizationHeaderCopy = new GrpcHeaderCopy("authorization");
    private TriathlonServiceBlockingStub blockingStub;
    private ManagedChannel channel;
    private Arbiter arbiter;

    public GrpcService(String serverAddress, int serverPort) {
        this.serverAddress = serverAddress;
        this.serverPort = serverPort;
    }

    public boolean isStarted() {
        return channel != null && !channel.isShutdown() && !channel.isTerminated();
    }

    @Override
    public void start() throws CanStartError {
        if (isStarted()) {
            return;
        }

        channel = ManagedChannelBuilder.forAddress(serverAddress, serverPort)
                .usePlaintext()
                .build();
        blockingStub = TriathlonServiceGrpc.newBlockingStub(channel)
                .withInterceptors(authorizationHeaderCopy);
    }

    @Override
    public void stop() throws CanStartError {
        if (!isStarted()) {
            return;
        }

        channel.shutdown();
    }

    @Override
    public Arbiter getLoggedInArbiter() {
        return arbiter;
    }

    public void handleLogin(Arbiter arbiter) {
        Arbiter oldArbiter = this.arbiter;
        this.arbiter = arbiter;

        if (oldArbiter != null) {
            return;
        }

        observersSendEvent(LOGIN_EVENT,true);
    }

    public void handleLogout(boolean requested) {
        if (arbiter == null) {
            return;
        }

        arbiter = null;
        if (!requested) {
            observersSendEvent(LOGIN_EVENT,false);
        }
    }

    public void handleLogout() {
        handleLogout(false);
    }

    public boolean handleLogout(ErrorNumber errorNumber) {
        switch (errorNumber) {
            case INVALID_LOGIN:
            case BEARER_MISSING:
            case BEARER_INVALID:
            case BEARER_NOT_AUTHORIZED:
                handleLogout();
                return true;
        }

        return false;
    }

    @Override
    public Arbiter loginArbiter(String name, String password) throws ServiceError {
        ArbiterLoginResponse response;

        try {
            start();
        } catch (CanStartError e) {
            throw new ServiceError(e);
        }

        try {
            response = blockingStub.loginArbiter(ArbiterLoginRequest.newBuilder()
                    .setName(name)
                    .setPassword(password)
                    .build());
        } catch (StatusRuntimeException e) {
            throw new ServiceError(ErrorNumber.CONNECTION_ERROR);
        }

        if (!response.hasArbiter()) {
            throw new ServiceError(response.getErrorNo());
        }

        Arbiter arbiter = Arbiter.fromProto(response.getArbiter());
        handleLogin(arbiter);

        return arbiter;
    }

    @Override
    public void logout() {
        if (!isStarted()) {
            return;
        }

        try {
            blockingStub.logout(ArbiterLogoutRequest.newBuilder().build());
        } catch (StatusRuntimeException ignored) {}

        handleLogout(true);
    }

    public List<Score> getScores(Iterator<ScoreResponse> responses) throws ServiceError {
        List<Score> scores = new ArrayList<>();
        while (responses.hasNext()) {
            ScoreResponse response = responses.next();

            if (!response.hasScore()) {
                if (!handleLogout(response.getErrorNo())) {
                    throw new ServiceError(response.getErrorNo());
                }
            }

            scores.add(Score.fromProto(response.getScore()));
        }
        return scores;
    }

    @Override
    public List<Score> getScores() throws ServiceError {
        Iterator<ScoreResponse> responses;
        try {
            responses = blockingStub.getScores(ScoresRequest.newBuilder().build());
        } catch (StatusRuntimeException e) {
            throw new ServiceError(ErrorNumber.CONNECTION_ERROR);
        }
        return getScores(responses);
    }

    @Override
    public List<Score> getRankings() throws ServiceError {
        Iterator<ScoreResponse> responses;
        try {
            responses = blockingStub.getRankings(ScoresRequest.newBuilder().build());
        } catch (StatusRuntimeException e) {
            throw new ServiceError(ErrorNumber.CONNECTION_ERROR);
        }
        return getScores(responses);
    }

    @Override
    public Score setScoreValue(int participantId, int value) throws ServiceError {
        ScoreResponse response;
        try {
            response = blockingStub.setScoreValue(SetScoreRequest.newBuilder()
                    .setParticipantId(participantId)
                    .setValue(value)
                    .build());
        } catch (StatusRuntimeException e) {
            throw new ServiceError(ErrorNumber.CONNECTION_ERROR);
        }

        if (!response.hasScore()) {
            if (!handleLogout(response.getErrorNo())) {
                throw new ServiceError(response.getErrorNo());
            }
        }

        return Score.fromProto(response.getScore());
    }
}
