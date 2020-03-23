package domain;

import repository.DatabaseField;
import repository.DatabaseTable;

@DatabaseTable(name="Participants")
public class Participant {

    @DatabaseField(name="ParticipantName", type="nvarchar(255)", primaryKey=true, notNull=true)
    private String name;

    public Participant() {}

    public Participant(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "Participant{" +
                "name='" + name + '\'' +
                '}';
    }
}
