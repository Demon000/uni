package message;

import java.io.IOException;
import java.net.Socket;

public abstract class MessageHandler extends ObjectHandler {
    protected MessageHandler(Socket socket) throws IOException {
        super(socket);
    }

    public void send(Message message) {
        super.send(message);
    }

    public void send(MessageType type, Object data) {
        send(new Message(type, data));
    }

    public void send(MessageType type) {
        send(new Message(type, null));
    }
}
