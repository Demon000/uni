package domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import static utils.StringUtils.matchesAny;
import static utils.XMLUtils.*;

public class Assignment extends BaseEntity<String> {
    public static final String TAG_NAME = "assignment";

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

    public String getStartWeekString() {
        return String.valueOf(getStartWeek());
    }

    public void setStartWeek(long startWeek) {
        this.startWeek = startWeek;
    }

    public long getDeadlineWeek() {
        return deadlineWeek;
    }

    public String getDeadlineWeekString() {
        return String.valueOf(getDeadlineWeek());
    }

    public void setDeadlineWeek(long deadlineWeek) {
        this.deadlineWeek = deadlineWeek;
    }

    public long getNumberOfWeeks() {
        return deadlineWeek - startWeek + 1;
    }

    public String toString() {
        return String.format("Assignment -> id: %s, description: %s, start week: %d, deadline week: %d",
                getId(), getDescription(), getStartWeek(), getDeadlineWeek());
    }

    public boolean matches(String input) {
        return matchesAny(input, getId(), getDescription(),
                getStartWeekString(), getDeadlineWeekString());
    }

    public Element toXMLElement(Document document) {
        Element assignmentElement = document.createElement(TAG_NAME);

        appendChildValue(assignmentElement, "id", getId());
        appendChildValue(assignmentElement, "description", getDescription());
        appendChildValue(assignmentElement, "startWeek", getStartWeekString());
        appendChildValue(assignmentElement, "deadlineWeek", getDeadlineWeekString());

        return assignmentElement;
    }

    public static Assignment createFromXMLElement(Element element) {
        String id = getChildValue(element, "id");
        String description = getChildValue(element, "description");
        long startWeek = Long.parseLong(getChildValue(element, "startWeek"));
        long deadlineWeek = Long.parseLong(getChildValue(element, "deadlineWeek"));

        return new Assignment(id, description, startWeek, deadlineWeek);
    }

    public static class Builder implements IBuilder<String, Assignment> {
        @Override
        public Assignment buildFromXML(Element element) {
            return Assignment.createFromXMLElement(element);
        }
    }
}
