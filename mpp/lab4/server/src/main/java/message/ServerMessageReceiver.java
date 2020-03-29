package message;

public interface ServerMessageReceiver extends ObjectReceiver {
    default void onLoginRequest(ServerMessageHandler messageHandler, LoginData data) {}
    default void onParticipantScoresRequest(ServerMessageHandler messageHandler) {}
    default void onRankingScoresRequest(ServerMessageHandler messageHandler) {}
    default void onSetScoreRequest(ServerMessageHandler messageHandler, ScoreSetData data) {}
}
