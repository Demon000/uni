package Domain;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Grade extends BaseEntity<String> {
    private LocalDate date;
    private int value;
    private long penalty;

    public Grade(String id, int value, long penalty, LocalDate date) {
        setId(id);

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

    public long getPenalty() {
        return penalty;
    }

    public void setPenalty(int penalty) {
        this.penalty = penalty;
    }

    public String toString() {
        final DateTimeFormatter dateFormatter = new DateTimeFormatter.ofPattern("dd/mm/yyyy");
        return String.format("Grade -> id: %s, date: %s, value: %d", getId(), date.format(dateFormatter), value);
    }
}
