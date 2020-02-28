package domain;

public class Answer extends BaseEntity<String> {
    private final float points;

    public Answer(int questionId, String studentName, float points) {
        super(questionId + "+" + studentName);

        this.points = points;
    }

    public String[] getIdParts() {
        return getId().split("\\+");
    }

    public int getQuestionId() {
        return Integer.parseInt(getIdParts()[0]);
    }

    public String getStudentName() {
        return getIdParts()[1];
    }

    public float getPoints() {
        return points;
    }
}
