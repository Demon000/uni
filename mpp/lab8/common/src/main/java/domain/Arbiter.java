package domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonInclude;

import javax.persistence.*;
import java.io.Serializable;

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

    @JsonIgnoreProperties(ignoreUnknown = true)
    @JsonInclude(JsonInclude.Include.NON_NULL)
    public static class PostDocument implements Serializable {
        private Integer id;

        public PostDocument(Integer id) {
            this.id = id;
        }

        public PostDocument() {
            this(null);
        }

        public Integer getId() {
            return id;
        }

        public void setId(Integer id) {
            this.id = id;
        }

        @Override
        public String toString() {
            return "PostDocument{" +
                    "id=" + id +
                    '}';
        }
    }
}
