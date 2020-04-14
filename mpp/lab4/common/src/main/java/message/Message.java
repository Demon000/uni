package message;

import java.io.Serializable;

public class Message implements Serializable {
    public final MessageType type;
    public final Object data;

    public Message(MessageType type, Object data) {
        this.type = type;
        this.data = data;
    }

    @Override
    public String toString() {
        return String.format("Message => type: %s, data: %s", type, data);
    }
}
