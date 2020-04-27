package domain;

import grpc.triathlon.ArbiterProto;

import java.io.Serializable;

public class Arbiter implements Serializable {
    private int id = 0;
    private final String name;
    private final ScoreType type;

    public Arbiter(String name, ScoreType type) {
        this.name = name;
        this.type = type;
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

    public ScoreType getType() {
        return type;
    }

    public static Arbiter fromProto(ArbiterProto proto) {
        return new Arbiter(proto.getName(), ScoreType.fromProto(proto.getType()));
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
