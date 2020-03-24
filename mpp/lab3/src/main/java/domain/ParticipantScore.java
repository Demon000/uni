package domain;

import java.util.HashMap;
import java.util.Map;

public class ParticipantScore {
    private final Participant participant;
    private final Map<ScoreType, Integer> scores = new HashMap<>();


    public ParticipantScore(Participant participant) {
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
