package Domain;

import java.util.ArrayList;
import java.util.List;

public class Student extends BaseEntity<String> {
    private String firstName;
    private String lastName;
    private String email;
    private String group;

    public Student(String id,  String firstName, String lastName, String email, String group) {
        setId(id);

        this.firstName = firstName;
        this.lastName = lastName;
        this.email = email;
        this.group = group;
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

    @Override
    public String toString() {
        return String.format("Student -> id: %s, name: %s %s, email: %s, group: %s",
                getId(), firstName, lastName, email, group);
    }
}
