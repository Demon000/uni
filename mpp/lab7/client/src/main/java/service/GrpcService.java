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

public class GrpcService extends BaseService {
    private final String serverAddress;
    private final Integer serverPort;

    private final GrpcHeaderCopy authorizationHeaderCopy = new GrpcHeaderCopy("authorization");
    private ChannelStateListener listener = new ChannelStateListener(this::onConnectivityStateChange);
    private OnSetScoreObserver onSetScoreObserver;
    private TriathlonServiceBlockingStub blockingStub;
    private TriathlonServiceStub asyncStub;
    private ManagedChannel channel;

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

    private void onConnectivityStateChange(ConnectivityState state) {
        observersConnectionStatusChange(getConnectionStatus(state));
    }

    public void subscribeSetScore() {
        if (isStarted() && onSetScoreObserver == null && observers.size() != 0) {
            onSetScoreObserver = new OnSetScoreObserver();
            asyncStub.subscribeSetScore(SubscribeSetScoreRequest.newBuilder().build(), onSetScoreObserver);
        }
    }

    public void unsubscribeSetScore() {
        if (isStarted() && onSetScoreObserver != null && observers.size() == 0) {
            try {
                blockingStub.unsubscribeSetScore(UnsubscribeSetScoreRequest.newBuilder().build());
            } catch (StatusRuntimeException ignored) {
            }
            onSetScoreObserver = null;
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

        return Arbiter.fromProto(response.getArbiter());
    }

    public List<Score> getScores(Iterator<ScoreResponse> responses) throws ServiceError {
        List<Score> scores = new ArrayList<>();
        while (responses.hasNext()) {
            ScoreResponse response = responses.next();
            if (!response.hasScore()) {
                throw new ServiceError(response.getErrorNo());
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
            throw new ServiceError(response.getErrorNo());
        }

        return Score.fromProto(response.getScore());
    }
}
