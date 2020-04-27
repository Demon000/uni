package domain;

import grpc.triathlon.ScoreProto;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.function.BiConsumer;

public class Score implements Serializable {
    private final Participant participant;
    private Map<ScoreType, Integer> scores = new HashMap<>();

    public Score(Participant participant) {
        this.participant = participant;
    }

    public Participant getParticipant() {
        return participant;
    }

    public int getScore(ScoreType type) {
        return scores.getOrDefault(type, 0);
    }

    public void setScore(ScoreType type, int score) {
        scores.put(type, score);
    }

    public void setScores(Map<ScoreType, Integer> scores) {
        this.scores = scores;
    }

    public Map<ScoreType, Integer> getScores() {
        return scores;
    }

    public int getTotalScore() {
        return scores.values().stream().reduce(0, Integer::sum);
    }

    public static Score fromProto(ScoreProto proto) {
        Participant participant = Participant.fromProto(proto.getParticipant());
        Score score = new Score(participant);
        proto.getScoresMap().forEach((key, value) -> {
            ScoreType type = ScoreType.fromInteger(key);
            score.setScore(type, value);
        });
        return score;
    }

    @Override
    public String toString() {
        return "ParticipantScore{" +
                "participant=" + participant +
                ", totalScore=" + getTotalScore() +
                '}';
    }
}
