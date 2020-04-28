package service;

import domain.Arbiter;
import domain.Score;
import grpc.triathlon.*;
import grpc.triathlon.TriathlonServiceGrpc.TriathlonServiceBlockingStub;
import grpc.triathlon.TriathlonServiceGrpc.TriathlonServiceStub;
import io.grpc.*;
import io.grpc.stub.StreamObserver;
import utils.GrpcHeaderCopy;

import java.util.*;

public class GrpcService extends BaseService implements ChannelStateListener.StateListener {
    private final String serverAddress;
    private final Integer serverPort;

    private final GrpcHeaderCopy authorizationHeaderCopy = new GrpcHeaderCopy("authorization");
    private final ChannelStateListener listener = new ChannelStateListener(this);
    private OnSetScoreObserver onSetScoreObserver = new OnSetScoreObserver();
    private TriathlonServiceBlockingStub blockingStub;
    private TriathlonServiceStub asyncStub;
    private ManagedChannel channel;
    private Arbiter arbiter;

    public GrpcService(String serverAddress, Integer serverPort) {
        this.serverAddress = serverAddress;
        this.serverPort = serverPort;
    }

    public boolean isStarted() {
        return channel != null && !channel.isShutdown() && !channel.isTerminated();
    }

    @Override
    public void start() {
        if (isStarted()) {
            return;
        }

        channel = ManagedChannelBuilder.forAddress(serverAddress, serverPort)
                .usePlaintext()
                .build();
        listener.setChannel(channel);
        blockingStub = TriathlonServiceGrpc.newBlockingStub(channel)
                .withInterceptors(authorizationHeaderCopy);
        asyncStub = TriathlonServiceGrpc.newStub(channel)
                .withInterceptors(authorizationHeaderCopy);

        subscribeSetScore();
    }

    @Override
    public void stop() {
        if (!isStarted()) {
            return;
        }

        channel.shutdown();
    }

    private ServiceConnectionStatus getConnectionStatus(ConnectivityState state) {
        if (state == ConnectivityState.READY) {
            return ServiceConnectionStatus.CONNECTED;
        } else {
            return ServiceConnectionStatus.DISCONNECTED;
        }
    }

    public ServiceConnectionStatus getConnectionStatus() {
        return getConnectionStatus(channel.getState(false));
    }

    @Override
    public void onStateChanged(ConnectivityState oldState, ConnectivityState newState) {
        if (oldState == ConnectivityState.TRANSIENT_FAILURE && newState == ConnectivityState.READY) {
            ping();
        }

        observersConnectionStatusChange(getConnectionStatus(newState));
    }

    public void subscribeSetScore() {
        if (isStarted()) {
            asyncStub.subscribeSetScore(SubscribeSetScoreRequest.newBuilder().build(), onSetScoreObserver);
        }
    }

    public void unsubscribeSetScore() {
        if (isStarted()) {
            blockingStub.unsubscribeSetScore(UnsubscribeSetScoreRequest.newBuilder().build());
        }
    }

    @Override
    public void onAddFirstObserver(IServiceObserver observer) {
        subscribeSetScore();
    }

    @Override
    public void onRemoveLastObserver(IServiceObserver observer) {
        unsubscribeSetScore();
    }

    private class OnSetScoreObserver implements StreamObserver<ScoreResponse> {
        @Override
        public void onNext(ScoreResponse response) {
            if (response.hasScore()) {
                observerSetScore(Score.fromProto(response.getScore()));
            }
        }

        @Override
        public void onError(Throwable t) {
            t.printStackTrace();
        }

        @Override
        public void onCompleted() {}
    }

    @Override
    public Arbiter getLoggedInArbiter() {
        return arbiter;
    }

    @Override
    public boolean ping() {
        PingResponse response;
        try {
            response = blockingStub.ping(PingRequest.newBuilder().build());
        } catch (StatusRuntimeException e) {
            return false;
        }

        if (!response.getLoggedIn()) {
            handleLogout();
        }

        return response.getLoggedIn();
    }

    public void handleLogin(Arbiter arbiter) {
        Arbiter oldArbiter = this.arbiter;
        this.arbiter = arbiter;

        if (oldArbiter != null) {
            return;
        }

        observersLoginStatusChange(true);
    }

    public void handleLogout(boolean requested) {
        if (arbiter == null) {
            return;
        }

        arbiter = null;
        if (!requested) {
            observersLoginStatusChange(false);
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

        subscribeSetScore();

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
