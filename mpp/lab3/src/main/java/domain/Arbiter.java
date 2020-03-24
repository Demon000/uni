package domain;

public class Arbiter {
    private int id = 0;
    private final String name;
    private final String password;
    private final ScoreType type;

    public Arbiter(String name, String password, ScoreType type) {
        this.name = name;
        this.password = password;
        this.type = type;
    }

    public Arbiter(int id, String name, String password, ScoreType type) {
        this(name, password, type);

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

    public String getPassword() {
        return password;
    }

    public ScoreType getType() {
        return type;
    }

    @Override
    public String toString() {
        return "Arbiter{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", type=" + type +
                '}';
    }
}
