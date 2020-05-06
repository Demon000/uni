package domain;

import com.fasterxml.jackson.annotation.JsonAutoDetect;

import javax.persistence.*;
import java.io.Serializable;

@JsonAutoDetect
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

    public static class PostDocument {
        private final Integer id;
        private final String name;
        private final Integer arbiterId;

        public PostDocument(Integer id, String name, Integer arbiterId) {
            this.id = id;
            this.name = name;
            this.arbiterId = arbiterId;
        }

        public PostDocument() {
            this(null, null, null);
        }

        public Integer getId() {
            return id;
        }

        public String getName() {
            return name;
        }

        public Integer getArbiterId() {
            return arbiterId;
        }
    }
}
