package Domain;

import java.util.Objects;

public class Assignment extends BaseEntity<String> {
    private String description;
    private long startWeek;
    private long deadlineWeek;

    public Assignment(String id, String description, long startWeek, long deadlineWeek) {
        setId(id);

        this.description = description;
        this.startWeek = startWeek;
        this.deadlineWeek = deadlineWeek;
    }

    @Override
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        }

        if (!(other instanceof  Assignment)) {
            return false;
        }

        Assignment otherAssignment = (Assignment) other;

        return getId() == otherAssignment.getId();
    }

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public long getStartWeek() {
        return startWeek;
    }

    public void setStartWeek(long startWeek) {
        this.startWeek = startWeek;
    }

    public long getDeadlineWeek() {
        return deadlineWeek;
    }

    public void setDeadlineWeek(long deadlineWeek) {
        this.deadlineWeek = deadlineWeek;
    }
}
