package domain;

import java.util.HashMap;
import java.util.Map;

public class Score {
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

    @Override
    public String toString() {
        return "ParticipantScore{" +
                "participant=" + participant +
                ", totalScore=" + getTotalScore() +
                '}';
    }
}
