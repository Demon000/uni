package domain;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonInclude;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name="Races")
@JsonIgnoreProperties(ignoreUnknown = true)
@JsonInclude(JsonInclude.Include.NON_NULL)
public class Race implements Serializable {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name = "RaceId")
    private Integer id;

    @Column(name = "RaceName")
    private String name;

    @OneToOne(targetEntity = Arbiter.class, fetch = FetchType.EAGER)
    private Arbiter arbiter;

    public Race(Integer id, String name, Arbiter arbiter) {
        this.arbiter = arbiter;
        this.id = id;
        this.name = name;
    }

    public Race(String name, Arbiter arbiter) {
        this(null, name, arbiter);
    }

    public Race() {
        this(null, null);
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Arbiter getArbiter() {
        return arbiter;
    }

    public void setArbiter(Arbiter arbiter) {
        this.arbiter = arbiter;
    }

    @Override
    public String toString() {
        return "Race{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", arbiter=" + arbiter +
                '}';
    }
}
