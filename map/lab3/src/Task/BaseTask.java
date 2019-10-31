package Task;

import java.util.Objects;

public abstract class BaseTask {
    protected String id;
    protected String description;

    public BaseTask(String id, String description) {
        this.id = id;
        this.description = description;
    }

    public abstract void execute();

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    @Override
    public boolean equals(Object other) {
        if (this == other) {
            return true;
        }

        if (!(other instanceof BaseTask)) {
            return false;
        }

        BaseTask otherTask = (BaseTask) other;

        if (!id.equals(otherTask.getId())) {
            return false;
        }

        if (!description.equals(otherTask.getDescription())) {
            return false;
        }

        return true;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, description);
    }

    @Override
    public String toString() {
        return String.format("BaseTask => id: %s, description: %s", id, description);
    }
}