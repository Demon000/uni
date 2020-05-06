package domain;

import com.fasterxml.jackson.annotation.JsonAutoDetect;
import com.fasterxml.jackson.annotation.JsonIgnore;

import javax.persistence.*;
import java.io.Serializable;

@JsonAutoDetect
@Entity
@Table(name="Arbiters")
public class Arbiter implements Serializable {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name = "ArbiterId")
    private final Integer id;

    @Column(name = "ArbiterName")
    private final String name;

    @JsonIgnore
    @Column(name = "ArbiterPassword")
    private final String password;

    public Arbiter(Integer id, String name, String password) {
        this.name = name;
        this.password = password;
        this.id = id;
    }

    public Arbiter(String name, String password) {
        this(null, name, password);
    }

    public Arbiter() {
        this(null, null);
    }

    public Integer getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getPassword() {
        return password;
    }

    @Override
    public String toString() {
        return "Arbiter{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }
}
