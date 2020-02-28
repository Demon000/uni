package domain;

public class QuestionStringSerializer implements ISerializer<Integer, Question, String> {
    @Override
    public String serialize(Question question) {
        return String.format("%d\t%s\t%s\t%s\t%s\t%d\t%f", question.getId(),
                question.getDescription(), question.getFirstChoice(),
                question.getSecondChoice(), question.getThirdChoice(),
                question.getCorrectChoice(), question.getPoints());
    }

    @Override
    public Question deserialize(String line) {
        String[] parts = line.split("\\t");
        int id = Integer.parseInt(parts[0]);
        String description = parts[1];
        String firstChoice = parts[2];
        String secondChoice = parts[3];
        String thirdChoice = parts[4];
        int correctChoice = Integer.parseInt(parts[5]);
        float points = Float.parseFloat(parts[6]);
        return new Question(id, description, firstChoice, secondChoice, thirdChoice, correctChoice, points);
    }
}
