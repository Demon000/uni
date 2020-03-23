package domain;

import repository.DatabaseField;
import repository.DatabaseTable;

@DatabaseTable(name="Arbiters")
public class Arbiter {
    @DatabaseField(name="ArbiterName", type="nvarchar(255)", primaryKey=true, notNull=true)
    private String name;

    @DatabaseField(name="ArbiterType", type="integer", notNull=true)
    private int type;

    public Arbiter() {}

    public Arbiter(String name, int type) {
        this.name = name;
        this.type = type;
    }

    public  Arbiter(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    @Override
    public String toString() {
        return "Arbiter{" +
                "name='" + name + '\'' +
                ", type=" + type +
                '}';
    }
}
