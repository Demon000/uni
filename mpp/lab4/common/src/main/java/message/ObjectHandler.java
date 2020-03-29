package message;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class ObjectHandler {
    protected final String SENDER_THREAD_NAME = "ObjectHandlerSender";
    protected final String RECEIVER_THREAD_NAME = "ObjectHandlerReceiver";
    protected final String SENDER_THREAD_NAME_FORMAT = SENDER_THREAD_NAME + " - %s";
    protected final String RECEIVER_THREAD_NAME_FORMAT = RECEIVER_THREAD_NAME + " - %s";
    protected final Logger logger = LogManager.getLogger();

    protected final List<ObjectReceiver> receivers = new ArrayList<>();

    private final BlockingQueue<Object> outboundObjects = new LinkedBlockingQueue<>();
    private final ObjectOutputStream outputStream;
    protected final Thread sender;

    private final ObjectInputStream inputStream;
    protected final Thread receiver;

    private final Socket socket;

    protected ObjectHandler(Socket socket) throws IOException {
        this.socket = socket;
        this.outputStream = new ObjectOutputStream(socket.getOutputStream());
        this.inputStream = new ObjectInputStream(socket.getInputStream());

        this.sender = new Thread(() -> {
            logger.info("started running sender thread");
            while (!Thread.interrupted()) {
                Object object;
                try {
                    logger.info("waiting for object to be sent");
                    object = outboundObjects.take();
                    logger.info("found object to be sent");
                } catch (InterruptedException e) {
                    logger.error("thread interrupted");
                    return;
                }

                try {
                    logger.debug("sending object {}", object);
                    ObjectHandler.this.outputStream.writeObject(object);
                    logger.info("sent object");
                } catch (IOException e) {
                    logger.error("socket closed");
                    return;
                }
            }
        }, SENDER_THREAD_NAME);

        this.receiver = new Thread(() -> {
            logger.info("started running receiver thread");
            while (!Thread.interrupted()) {
                Object object;
                try {
                    logger.info("waiting for object to be received");
                    object = ObjectHandler.this.inputStream.readObject();
                    logger.info("found object to be received");
                } catch (IOException e) {
                    logger.error("socket closed");
                    return;
                } catch (ClassNotFoundException e) {
                    logger.error("thread was interrupted");
                    return;
                }

                logger.info("calling receive handlers");
                ObjectHandler.this.objectReceived(object);
            }
        }, RECEIVER_THREAD_NAME);
    }

    public void setThreadNames(String id) {
        sender.setName(String.format(SENDER_THREAD_NAME_FORMAT, id));
        receiver.setName(String.format(RECEIVER_THREAD_NAME_FORMAT, id));
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
