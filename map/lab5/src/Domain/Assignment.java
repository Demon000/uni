package Domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import static Utils.XMLUtils.*;

public class Assignment extends BaseEntity<String> {
    public static String TAG_NAME = "assignment";

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

    public String toString() {
        return String.format("Assignment -> id: %s, description: %s, start week: %d, deadline week: %d",
                getId(), getDescription(), getStartWeek(), getDeadlineWeek());
    }

    public Element toXMLElement(Document document) {
        Element assignmentElement = document.createElement(TAG_NAME);

        appendChildValue(assignmentElement, "id", getId());
        appendChildValue(assignmentElement, "description", getDescription());
        appendChildValue(assignmentElement, "startWeek", String.valueOf(getStartWeek()));
        appendChildValue(assignmentElement, "deadlineWeek", String.valueOf(getDeadlineWeek()));

        return assignmentElement;
    }

    public static Assignment createFromXMLElement(Element element) {
        String id = getChildValue(element, "id");
        String description = getChildValue(element, "description");
        long startWeek = Long.parseLong(getChildValue(element, "startWeek"));
        long deadlineWeek = Long.parseLong(getChildValue(element, "deadlineWeek"));

        return new Assignment(id, description, startWeek, deadlineWeek);
    }
}
