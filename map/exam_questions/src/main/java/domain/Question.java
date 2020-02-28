package domain;

public class Question extends BaseEntity<Integer> {
    private final String description;
    private final String firstChoice;
    private final String secondChoice;
    private final String thirdChoice;
    private final int correctChoice;
    private float points;

    public Question(int id, String description, String firstChoice, String secondChoice, String thirdChoice,
             int correctChoice, float points) {
        super(id);

        this.description = description;
        this.firstChoice = firstChoice;
        this.secondChoice = secondChoice;
        this.thirdChoice = thirdChoice;
        this.correctChoice = correctChoice;
        this.points = points;
    }
    
    public boolean isCorrectChoice(int givenChoice) {
        return correctChoice == givenChoice;
    }

    public String getDescription() {
        return description;
    }

    public String getFirstChoice() {
        return firstChoice;
    }

    public String getSecondChoice() {
        return secondChoice;
    }

    public String getThirdChoice() {
        return thirdChoice;
    }

    public float getPoints() {
        return points;
    }

    public int getCorrectChoice() {
        return correctChoice;
    }
}
