package Domain;

import java.time.LocalDate;

public class Grade extends BaseEntity<String> {
    private LocalDate date;
    private int value;
    private int penalty;

    public Grade(Student student, Assignment assignment,
                 int value, int penalty, LocalDate date) {
        setId(student.getId() + "+" + assignment.getId());

        this.value = value;
        this.penalty = penalty;
        this.date = date;
    }

    public LocalDate getDate() {
        return date;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getPenalty() {
        return penalty;
    }

    public void setPenalty(int penalty) {
        this.penalty = penalty;
    }
}
