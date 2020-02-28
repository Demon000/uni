package domain;

public class AnswerStringSerializer implements ISerializer<String, Answer, String> {
    @Override
    public String serialize(Answer answer) {
        return String.format("%d\t%s\t%f", answer.getQuestionId(), answer.getStudentName(), answer.getPoints());
    }

    @Override
    public Answer deserialize(String line) {
        String[] parts = line.split("\\t");
        int questionId = Integer.parseInt(parts[0]);
        String studentName = parts[1];
        float points = Float.parseFloat(parts[2]);

        return new Answer(questionId, studentName, points);
    }
}
