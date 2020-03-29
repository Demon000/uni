package message;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ObjectHandler {
    protected final List<ObjectReceiver> receivers = new ArrayList<>();

    private final BlockingQueue<Object> outboundObjects = new LinkedBlockingQueue<>();
    private final ObjectOutputStream outputStream;
    private final Thread sender;

    private final ObjectInputStream inputStream;
    private final Thread receiver;

    private final Socket socket;

    protected ObjectHandler(Socket socket) throws IOException {
        this.socket = socket;
        this.outputStream = new ObjectOutputStream(socket.getOutputStream());
        this.inputStream = new ObjectInputStream(socket.getInputStream());

        this.sender = new Thread(() -> {
            System.out.println("Sender: tarted running sender thread");
            while (!Thread.interrupted()) {
                Object object;
                try {
                    System.out.println("Sender: waiting for object to be sent");
                    object = outboundObjects.take();
                    System.out.println("Sender: found object to be sent");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    return;
                }

                try {
                    System.out.println(String.format("Sender: sending object %s", object));
                    ObjectHandler.this.outputStream.writeObject(object);
                    System.out.println("Sender: sent object");
                } catch (IOException e) {
                    e.printStackTrace();
                    return;
                }
            }
        }, "ObjectHandlerSender");

        this.receiver = new Thread(() -> {
            System.out.println("Receiver: started running receiver thread");
            while (!Thread.interrupted()) {
                Object object;
                try {
                    System.out.println("Receiver: waiting for object to be received");
                    object = ObjectHandler.this.inputStream.readObject();
                    System.out.println("Receiver: found object to be received");
                } catch (IOException | ClassNotFoundException e) {
                    e.printStackTrace();
                    return;
                }

                System.out.println("Receiver: calling receive handlers");
                ObjectHandler.this.objectReceived(object);
            }
        }, "ObjectHandlerReceiver");
    }

    public void start() {
        sender.start();
        receiver.start();
    }

    public void stop() throws IOException {
        this.receiver.interrupt();
        this.sender.interrupt();
        this.socket.close();
    }

    protected void addReceiver(ObjectReceiver receiver) {
        receivers.add(receiver);
    }

    protected void removeReceiver(ObjectReceiver receiver) {
        receivers.remove(receiver);
    }

    protected void objectReceived(Object object) {
        receivers.forEach(receiver -> receiver.onReceive(object));
    }

    protected void send(Object object) {
        outboundObjects.add(object);
    }
}
