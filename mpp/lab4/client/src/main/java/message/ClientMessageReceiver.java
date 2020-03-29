package message;

import domain.Arbiter;
import domain.Score;

import java.util.List;

public interface ClientMessageReceiver extends ObjectReceiver {
    default void onLoginRequestError(String error) {}
    default void onLoginResponse(Arbiter arbiter) {}
    default void onParticipantScoresRequestError(String error) {}
    default void onParticipantScoresResponse(List<Score> scores) {}
    default void onRankingScoresRequestError(String error) {}
    default void onRankingScoresResponse(List<Score> scores) {}
    default void onSetScoreRequestError(String error) {}
    default void onSetScoreBroadcast(Score score) {}
}
