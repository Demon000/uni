package domain;

import java.io.Serializable;

public class Participant implements Serializable {
    private int id = 0;
    private final String name;

    public Participant(String name) {
        this.name = name;
    }

    public Participant(int id, String name) {
        this(name);

        this.id = id;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Participant{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }
}
