package domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonInclude;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name="Arbiters")
@JsonIgnoreProperties(ignoreUnknown = true)
@JsonInclude(JsonInclude.Include.NON_NULL)
public class Arbiter implements Serializable {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name = "ArbiterId")
    private Integer id;

    @Column(name = "ArbiterName")
    private String name;

    @JsonIgnore
    @Column(name = "ArbiterPassword")
    private String password;

    public Arbiter(Integer id, String name, String password) {
        this.name = name;
        this.password = password;
        this.id = id;
    }

    public Arbiter(String name, String password) {
        this(null, name, password);
    }

    public Arbiter(Integer id) {
        this(id, null, null);
    }

    public Arbiter() {
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

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "Arbiter{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }
}
