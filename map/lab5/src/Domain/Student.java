package Domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import static Utils.XMLUtils.*;

public class Student extends BaseEntity<String> {
    public static String TAG_NAME = "student";

    private List<Long> motivatedWeeks;
    private String firstName;
    private String lastName;
    private String email;
    private String group;

    public Student(String id,  String firstName, String lastName, String email, String group, List<Long> motivatedWeeks) {
        setId(id);

        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.group = group;
        this.motivatedWeeks = motivatedWeeks;
    }

    public Student(String id, String firstName, String lastName, String email, String group) {
        this(id, firstName, lastName, email, group, new ArrayList<>());
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

    public boolean removeMotivatedWeek(long w) {
        Long week = w;
        return motivatedWeeks.remove(week);
    }

    @Override
    public String toString() {
        String motivatedWeeksString;

        if (motivatedWeeks.size() > 0) {
            motivatedWeeksString = motivatedWeeks.stream()
                    .sorted()
                    .map(Object::toString)
                    .collect(Collectors.joining(", "));
        } else {
            motivatedWeeksString = "none";
        }

        return String.format("Student -> id: %s, name: %s %s, email: %s, group: %s,\n\tmotivated weeks: %s",
                getId(), getFirstName(), getLastName(), getEmail(), getGroup(), motivatedWeeksString);
    }

    public Element toXMLElement(Document document) {
        Element studentElement = document.createElement(TAG_NAME);

        appendChildValue(studentElement, "id", getId());
        appendChildValue(studentElement, "firstName", getFirstName());
        appendChildValue(studentElement, "lastName", getLastName());
        appendChildValue(studentElement, "email", getEmail());
        appendChildValue(studentElement, "group", getGroup());

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

        List<String> motivatedWeekStrings = getListChildrenValues(element, "motivatedWeeks",
                "motivatedWeek");

        List<Long> motivatedWeeks = motivatedWeekStrings.stream()
                .map(Long::parseLong)
                .collect(Collectors.toList());

        return new Student(id, firstName, lastName, email, group, motivatedWeeks);
    }
}
