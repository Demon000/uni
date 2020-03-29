package message;

import java.io.Serializable;

public class ScoreSetData implements Serializable {
    private final int participantId;
    private final int value;

    public ScoreSetData(int participantId, int value) {
        this.participantId = participantId;
        this.value = value;
    }

    public int getParticipantId() {
        return participantId;
    }

    public int getValue() {
        return value;
    }
}
