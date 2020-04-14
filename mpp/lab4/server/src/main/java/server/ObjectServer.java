package server;

import message.ServerMessageHandler;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import service.IService;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ObjectServer implements IServer {
    protected final Logger logger = LogManager.getLogger();

    private final List<ServerMessageHandler> messageHandlers = new ArrayList<>();
    private ServerSocket serverSocket;
    private IService service;
    private ClientConnection clientConnectionThread;

    private class ClientConnection extends Thread {
        public ClientConnection() {
            super("ClientConnection");
        }

        @Override
        public void run() {
            logger.info("started running connection thread");
            while (!Thread.interrupted()) {
                try {
                    logger.info("waiting for client connection");
                    Socket clientSocket = serverSocket.accept();
                    logger.info("client connected");
                    ServerMessageHandler messageHandler = new ServerMessageHandler(clientSocket, service);
                    synchronized (messageHandlers) {
                        messageHandlers.add(messageHandler);
                    }
                    messageHandler.start();
                } catch (IOException e) {
                    logger.error("thread interrupted");
                    return;
                }
            }
        }
    }

    public void start(IService service, int port) throws IOException {
        this.service = service;
        this.serverSocket = new ServerSocket(port);

        if (clientConnectionThread == null) {
            clientConnectionThread = new ClientConnection();
            clientConnectionThread.start();
        }
    }

    public void stop() throws IOException {
        if (clientConnectionThread != null) {
            clientConnectionThread.interrupt();
        }

        if (serverSocket.isBound()) {
            serverSocket.close();
        }

        synchronized (messageHandlers) {
            messageHandlers.forEach(handler -> {
                try {
                    handler.stop();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }
    }
}
