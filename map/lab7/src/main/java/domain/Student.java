package domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import static utils.XMLUtils.*;

public class Student extends BaseEntity<String> {
    public static final String TAG_NAME = "student";

    private List<Long> motivatedWeeks;
    private String firstName;
    private String lastName;
    private String email;
    private String group;
    private String professorName;

    public Student(String id, String firstName, String lastName, String email, String group, String professorName, List<Long> motivatedWeeks) {
        setId(id);

        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.group = group;
        this.professorName = professorName;
        this.motivatedWeeks = motivatedWeeks;
    }

    public Student(String id, String firstName, String lastName, String email, String group, String professorName) {
        this(id, firstName, lastName, email, group, professorName, new ArrayList<>());
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getGroup() {
        return group;
    }

    public void setGroup(String group) {
        this.group = group;
    }

    public String getProfessorName() {
        return professorName;
    }

    public void setProfessorName(String professorName) {
        this.professorName = professorName;
    }

    public List<Long> getMotivatedWeeks() {
        return motivatedWeeks;
    }

    public void setMotivatedWeeks(List<Long> motivatedWeeks) {
        this.motivatedWeeks = motivatedWeeks;
    }

    public void addMotivatedWeek(long w) {
        Long week = w;
        motivatedWeeks.remove(week);
        motivatedWeeks.add(week);
    }

    public void removeMotivatedWeek(long w) {
        Long week = w;
        motivatedWeeks.remove(week);
    }

    public static List<Long> stringToMotivatedWeeks(String motivatedWeeksString) {
        return Arrays.stream(motivatedWeeksString.split("\\s*,\\s*"))
                .map(Long::valueOf)
                .collect(Collectors.toList());
    }

    public void setMotivatedWeeksString(String motivatedWeeksString) {
        motivatedWeeks = stringToMotivatedWeeks(motivatedWeeksString);
    }

    public String getMotivatedWeeksString() {
        String motivatedWeeksString;

        if (motivatedWeeks.size() > 0) {
            motivatedWeeksString = motivatedWeeks.stream()
                    .sorted()
                    .map(Object::toString)
                    .collect(Collectors.joining(", "));
        } else {
            motivatedWeeksString = "none";
        }

        return motivatedWeeksString;
    }

    @Override
    public String toString() {
        return String.format("Student -> id: %s, name: %s %s, email: %s, group: %s, professor name: %s, \n\tmotivated weeks: %s",
                getId(), getFirstName(), getLastName(), getEmail(), getGroup(), getProfessorName(), getMotivatedWeeksString());
    }

    public Element toXMLElement(Document document) {
        Element studentElement = document.createElement(TAG_NAME);

        appendChildValue(studentElement, "id", getId());
        appendChildValue(studentElement, "firstName", getFirstName());
        appendChildValue(studentElement, "lastName", getLastName());
        appendChildValue(studentElement, "email", getEmail());
        appendChildValue(studentElement, "group", getGroup());
        appendChildValue(studentElement, "professorName", getProfessorName());

        List<String> motivatedWeekStrings = motivatedWeeks
                .stream()
                .map(Object::toString)
                .collect(Collectors.toList());

        appendListChildValues(studentElement, "motivatedWeeks", "motivatedWeek",
                motivatedWeekStrings);

        return studentElement;
    }

    public static Student createFromXMLElement(Element element) {
        String id = getChildValue(element, "id");
        String firstName = getChildValue(element, "firstName");
        String lastName = getChildValue(element, "lastName");
        String email = getChildValue(element, "email");
        String group = getChildValue(element, "group");
        String professorName = getChildValue(element, "professorName");

        List<Long> motivatedWeeks = getListChildrenValues(element, "motivatedWeeks", "motivatedWeek")
                .stream()
                .map(Long::parseLong)
                .collect(Collectors.toList());

        return new Student(id, firstName, lastName, email, group, professorName, motivatedWeeks);
    }

    public static class Builder implements IBuilder<String, Student> {
        @Override
        public Student buildFromXML(Element element) {
            return Student.createFromXMLElement(element);
        }
    }
}
