package Domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.List;

import static Utils.XMLUtils.appendChildValue;
import static Utils.XMLUtils.getChildValue;

public class Grade extends BaseEntity<String> {
    public static String TAG_NAME = "grade";

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
        final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
        String feedback = getFeedback();

        if (feedback.isEmpty()) {
            feedback = "none";
        }

        return String.format("Grade -> id: %s, date: %s, penalty: %d, value: %d, professor name: %s, \n\tfeedback: %s", getId(),
                date.format(dateFormatter), getPenalty(), getValue(), getProfessorName(), feedback);
    }

    public Element toXMLElement(Document document) {
        final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
        Element gradeElement = document.createElement(TAG_NAME);

        appendChildValue(gradeElement, "id", getId());
        appendChildValue(gradeElement, "date", getDate().format(dateFormatter));
        appendChildValue(gradeElement, "value", String.valueOf(getValue()));
        appendChildValue(gradeElement, "penalty", String.valueOf(getPenalty()));
        appendChildValue(gradeElement, "professorName", getProfessorName());
        appendChildValue(gradeElement, "feedback", getFeedback());

        return gradeElement;
    }

    public static Grade createFromXMLElement(Element element) {
        final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("d/MM/yyyy");
        String id = getChildValue(element, "id");
        LocalDate date = LocalDate.parse(getChildValue(element,"date"), dateFormatter);
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
