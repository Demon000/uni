package domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import static utils.StringUtils.matchesAny;
import static utils.XMLUtils.appendChildValue;
import static utils.XMLUtils.getChildValue;

public class Grade extends BaseEntity<String> {
    public static final String TAG_NAME = "grade";
    public static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("dd/MM/yyyy");

    private LocalDate date;
    private long penalty;
    private int value;
    private String professorName;
    private String feedback;

    public Grade(String id, LocalDate date, long penalty, int value, String professorName, String feedback) {
        setId(id);

        this.date = date;
        this.penalty = penalty;
        this.value = value;
        this.professorName = professorName;
        this.feedback = feedback;
    }

    public static String createCompositeId(String studentId, String assignmentId) {
        return studentId + "+" + assignmentId;
    }

    public String getStudentId() {
        String[] ids = getId().split("\\+");
        return ids[0];
    }

    public String getAssignmentId() {
        String[] ids = getId().split("\\+");
        return ids[1];
    }

    public LocalDate getDate() {
        return date;
    }

    public String getDateString() {
        return date.format(DATE_FORMATTER);
    }

    public static LocalDate getDateFromString(String dateString) {
        return LocalDate.parse(dateString, DATE_FORMATTER);
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public long getPenalty() {
        return penalty;
    }

    public String getPenaltyString() {
        return String.valueOf(getPenalty());
    }

    public void setPenalty(long penalty) {
        this.penalty = penalty;
    }

    public int getValue() {
        return value;
    }

    public String getValueString() {
        return String.valueOf(getValue());
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getProfessorName() {
        return professorName;
    }

    public void setProfessorName(String professorName) {
        this.professorName = professorName;
    }

    public String getFeedback() {
        return feedback;
    }

    public void setFeedback(String feedback) {
        this.feedback = feedback;
    }

    public String toString() {
        return String.format("Grade -> id: %s, date: %s, penalty: %d, value: %d, professor name: %s, \n\tfeedback: %s", getId(),
                getDateString(), getPenalty(), getValue(), getProfessorName(), getFeedback());
    }

    public boolean matches(String input) {
        return matchesAny(input, getId(), getDateString(), getPenaltyString(),
                getValueString(), getProfessorName(), getFeedback());
    }

    public Element toXMLElement(Document document) {
        Element gradeElement = document.createElement(TAG_NAME);

        appendChildValue(gradeElement, "id", getId());
        appendChildValue(gradeElement, "date", getDateString());
        appendChildValue(gradeElement, "value", String.valueOf(getValue()));
        appendChildValue(gradeElement, "penalty", String.valueOf(getPenalty()));
        appendChildValue(gradeElement, "professorName", getProfessorName());
        appendChildValue(gradeElement, "feedback", getFeedback());

        return gradeElement;
    }

    public static Grade createFromXMLElement(Element element) {
        String id = getChildValue(element, "id");
        LocalDate date = getDateFromString(getChildValue(element,"date"));
        int value = Integer.parseInt(getChildValue(element, "value"));
        long penalty = Long.parseLong(getChildValue(element, "penalty"));
        String professorName = getChildValue(element, "professorName");
        String feedback = getChildValue(element, "feedback");

        return new Grade(id, date, penalty, value, professorName, feedback);
    }

    public static class Builder implements IBuilder<String, Grade> {
        @Override
        public Grade buildFromXML(Element element) {
            return Grade.createFromXMLElement(element);
        }
    }
}
