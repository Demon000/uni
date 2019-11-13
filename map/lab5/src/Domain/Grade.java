package Domain;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Grade extends BaseEntity<String> {
    private LocalDate date;
    private int value;
    private long penalty;
    private String feedback;

    public Grade(String id, LocalDate date, long penalty, int value, String feedback) {
        setId(id);

        this.date = date;
        this.value = value;
        this.penalty = penalty;
        this.feedback = feedback;
    }

    public static String getCompositeId(String studentId, String assignmentId) {
        return studentId + "+" + assignmentId;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public long getPenalty() {
        return penalty;
    }

    public void setPenalty(long penalty) {
        this.penalty = penalty;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getFeedback() {
        return feedback;
    }

    public void setFeedback(String feedback) {
        this.feedback = feedback;
    }

    public String toString() {
        final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
        return String.format("Grade -> id: %s, date: %s, penalty: %d, value: %d,\n\tfeedback: %s", getId(),
                date.format(dateFormatter), penalty, value, feedback);
    }
}
