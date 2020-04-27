package domain;

import grpc.triathlon.ParticipantProto;

import java.io.Serializable;

public class Participant implements Serializable {
    private int id = 0;
    private final String name;

    public Participant(String name) {
        this.name = name;
    }

    public Participant(int id, String name) {
        this(name);

        this.id = id;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public static Participant fromProto(ParticipantProto proto) {
        return new Participant(proto.getId(), proto.getName());
    }

    @Override
    public String toString() {
        return "Participant{" +
                "id=" + id +
                ", name='" + name + '\'' +
                '}';
    }
}
