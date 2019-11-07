package Domain;

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
