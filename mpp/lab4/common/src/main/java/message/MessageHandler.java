package message;

import java.io.IOException;
import java.net.Socket;

public class MessageHandler extends ObjectHandler {
    public MessageHandler(Socket socket) throws IOException {
        super(socket);
    }

    public static MessageHandler createForAddress(String serverAddress, Integer serverPort) throws IOException {
        Socket socket = new Socket(serverAddress, serverPort);
        return new MessageHandler(socket);
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
