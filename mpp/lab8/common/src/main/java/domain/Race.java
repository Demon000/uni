package domain;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name="Races")
public class Race implements Serializable {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name = "RaceId")
    private final Integer id;

    @Column(name = "RaceName")
    private String name;

    @OneToOne(targetEntity = Arbiter.class, fetch = FetchType.EAGER)
    private Arbiter arbiter;

    public Race(Arbiter arbiter, Integer id, String name) {
        this.arbiter = arbiter;
        this.id = id;
        this.name = name;
    }

    public Race(Arbiter arbiter, String name) {
        this(arbiter, null, name);
    }

    public Race(String name) {
        this(null, name);
    }

    public Race() {
        this(null, "");
    }

    public int getId() {
        return id;
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

    @JsonIgnoreProperties(ignoreUnknown = true)
    public static class PostDocument implements Serializable {
        private Integer id;
        private String name;
        private Arbiter.PostDocument arbiter;

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

        public Arbiter.PostDocument getArbiter() {
            return arbiter;
        }

        public void setArbiter(Arbiter.PostDocument document) {
            this.arbiter = document;
        }
    }
}
