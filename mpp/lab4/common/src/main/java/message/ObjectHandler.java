package message;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public abstract class ObjectHandler {
    private final String SENDER_THREAD_NAME = "ObjectHandlerSender";
    private final String RECEIVER_THREAD_NAME = "ObjectHandlerReceiver";
    private final Logger logger = LogManager.getLogger();

    private final BlockingQueue<Object> outboundObjects = new LinkedBlockingQueue<>();
    private final ObjectOutputStream outputStream;
    private Sender senderThread;

    private final ObjectInputStream inputStream;
    private Receiver receiverThread;
    private IObjectReceiver receiver = null;

    private final Socket socket;

    protected ObjectHandler(Socket socket) throws IOException {
        this.socket = socket;
        this.outputStream = new ObjectOutputStream(socket.getOutputStream());
        this.inputStream = new ObjectInputStream(socket.getInputStream());
    }

    protected class Sender extends Thread {
        Sender() {
            super(SENDER_THREAD_NAME);
        }

        @Override
        public void run() {
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
                    outputStream.writeObject(object);
                    outputStream.flush();
                    logger.info("sent object");
                } catch (IOException e) {
                    logger.error("socket closed");
                    return;
                }
            }
        }
    }

    protected class Receiver extends Thread {
        Receiver() {
            super(RECEIVER_THREAD_NAME);
        }

        @Override
        public void run() {
            logger.info("started running receiver thread");
            while (!Thread.interrupted()) {
                Object object;
                try {
                    logger.info("waiting for object to be received");
                    object = inputStream.readObject();
                    logger.info("found object to be received");
                } catch (IOException e) {
                    logger.error("socket closed");
                    return;
                } catch (ClassNotFoundException e) {
                    logger.error("thread was interrupted");
                    return;
                }

                logger.info("calling receive handlers");
                onReceive(object);
            }
        }
    }

    protected void onReceive(Object object) {
        if (receiver != null) {
            receiver.onReceive(object);
        }
    }

    public void setReceiver(IObjectReceiver receiver) {
        this.receiver = receiver;
    }

    public void start() {
        if (senderThread == null) {
            senderThread = new Sender();
            senderThread.start();
        }

        if (receiverThread == null) {
            receiverThread = new Receiver();
            receiverThread.start();
        }
    }

    public void stop() throws IOException {
        if (receiverThread != null) {
            receiverThread.interrupt();
            receiverThread = null;
        }

        if (senderThread != null) {
            senderThread.interrupt();
            senderThread = null;
        }

        if (!socket.isClosed()) {
            socket.close();
        }
    }

    public void send(Object object) {
        outboundObjects.add(object);
    }
}
