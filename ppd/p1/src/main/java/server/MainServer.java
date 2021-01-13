package server;

import common.*;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

class Server {
    private final int NO_TASK_THREADS = 2;
    private final int NO_CHECKER_THREADS = 1;
    private final int NO_CHECK_INTERVAL_SECONDS = 5;
    private final int NO_RUNNING_TIME_SECONDS = 15;

    private Service service;

    private ServerSocket serverSocket;
    private final ExecutorService taskExecutor = Executors.newFixedThreadPool(NO_TASK_THREADS);
    private final ScheduledExecutorService checker = Executors.newScheduledThreadPool(NO_CHECKER_THREADS);
    AtomicBoolean running = new AtomicBoolean();

    public Server(Service service) {
        this.service = service;
    }

    class ClientHandler {
        private final Socket socket;
        ObjectInputStream in;
        ObjectOutputStream out;

        public ClientHandler(Socket socket) {
            this.socket = socket;
        }

        private void handleShowsRequest(ShowsRequest request) {
            CompletableFuture.supplyAsync(() -> {
                if (!running.get()) {
                    return new StatusResponse(false);
                }

                System.out.printf("Processing shows request %s%n", request.toString());

                return new ShowsResponse(service.getShows());
            }, taskExecutor).thenAccept(response -> {
                try {
                    out.writeObject(response);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }

        private void handleSaleRequest(SaleRequest request) {
            CompletableFuture.supplyAsync(() -> {
                if (!running.get()) {
                    return new StatusResponse(false);
                }

                System.out.printf("Processing sale request %s%n", request.toString());

                Sale sale;
                try {
                    sale = service.createSale(request.showId, request.seatIds);
                } catch (SaleError saleError) {
                    return saleError;
                }

                return new SaleResponse(sale);
            }, taskExecutor).thenAccept(response -> {
                try {
                    out.writeObject(response);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
        }

        public void run() {
            try {
                out = new ObjectOutputStream(socket.getOutputStream());
                in = new ObjectInputStream(socket.getInputStream());
            } catch (IOException e) {
                e.printStackTrace();
                return;
            }

            System.out.println("Client connected");

            Object request;
            try {
                request = in.readObject();
            } catch (IOException | ClassNotFoundException e) {
                e.printStackTrace();
                return;
            }

            System.out.printf("Request read %s%n", request.getClass().toString());

            if (request instanceof ShowsRequest) {
                handleShowsRequest((ShowsRequest) request);
            } else if (request instanceof SaleRequest) {
                handleSaleRequest((SaleRequest) request);
            } else {
                System.out.println("Invalid request type");
            }
        }
    }

    public void stop() {
        running.set(false);
    }

    public void finish() {
        checker.shutdown();
        taskExecutor.shutdown();
    }

    public void waitForClient() throws IOException {
        Socket socket;

        System.out.println("Waiting for a new client");

        try {
            socket = serverSocket.accept();
        } catch (SocketException e) {
            e.printStackTrace();
            return;
        }

        ClientHandler handler = new ClientHandler(socket);
        handler.run();
    }

    public void run(int port) throws IOException {
        running.set(true);

        serverSocket = new ServerSocket(port);

        System.out.printf("Server is running on port %d%n", port);

        checker.scheduleAtFixedRate(() -> {
            System.out.println("Checking consistency");
            try {
                service.checkConsistency();
            } catch (CheckError checkError) {
                checkError.printStackTrace();
            }
        }, NO_CHECK_INTERVAL_SECONDS, NO_CHECK_INTERVAL_SECONDS, TimeUnit.SECONDS);

        checker.schedule(() -> {
            System.out.println("Stopping server");
            stop();
        }, NO_RUNNING_TIME_SECONDS, TimeUnit.SECONDS);

        while (running.get()) {
            waitForClient();
        }

        finish();
    }
}

public class MainServer {
    public static void main(String[] args) {
        System.out.println("Hello world from server");

        Service service = new Service();

        service.createShow("First show", 100, 100);
        service.createShow("Second show", 200, 100);
        service.createShow("Third show", 150, 100);

        Server server = new Server(service);

        try {
            server.run(8080);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
