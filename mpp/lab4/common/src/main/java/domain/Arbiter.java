package domain;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name="Arbiters")
public class Arbiter implements Serializable {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name="ArbiterId")
    private int id = 0;

    @Column(name="ArbiterName")
    private final String name;

    @Column(name="ArbiterPassword")
    private final String password;

    @Column(name="ArbiterType")
    private final ScoreType type;

    public Arbiter() {
        this("", "", ScoreType.INVALID);
    }

    public Arbiter(String name, String password, ScoreType type) {
        this.name = name;
        this.password = password;
        this.type = type;
    }

    public Arbiter(String name, String password) {
        this(name, password, ScoreType.INVALID);
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
