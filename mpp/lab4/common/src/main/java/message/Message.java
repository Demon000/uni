package message;

import java.io.Serializable;

public class Message implements Serializable {
    public MessageType type;
    public Object data;

    public Message(MessageType type, Object data) {
        this.type = type;
        this.data = data;
    }

    @Override
    public String toString() {
        return "Message{" +
                "type=" + type +
                ", data=" + data +
                '}';
    }
}
