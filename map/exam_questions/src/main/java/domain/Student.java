package domain;

public class Student extends BaseEntity<String> {
    private boolean loggedIn;

    public Student(String name) {
        super(name);
    }

    public boolean getLoggedIn() {
        return loggedIn;
    }

    public void setLoggedIn(boolean loggedIn) {
        this.loggedIn = loggedIn;
    }
}
