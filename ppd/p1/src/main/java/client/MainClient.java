package client;

import common.*;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Random;

class Client {
    ArrayList<Show> shows;
    private String host;
    private int port;

    public ArrayList<Show> doShowsRequest() throws IOException, ClassNotFoundException {
        Socket socket = new Socket(host, port);

        ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream in = new ObjectInputStream(socket.getInputStream());

        out.writeObject(new ShowsRequest());

        Object response = in.readObject();

        if (response instanceof StatusResponse) {
            StatusResponse statusResponse = (StatusResponse) response;
            System.out.printf("Server responded with status %s\n", statusResponse.toString());
            return new ArrayList<>();
        } else if (response instanceof ShowsResponse) {
            ShowsResponse showsResponse = (ShowsResponse) response;
            System.out.printf("Server responded with shows %s%n", showsResponse.toString());
            for (Show show : showsResponse.shows) {
                System.out.println(show.toString());
            }
            System.out.println();
            return showsResponse.shows;
        }

        return new ArrayList<>();
    }

    public boolean doSaleRequest(int showId, ArrayList<Integer> seatIds) throws IOException, ClassNotFoundException {
        Socket socket = new Socket(host, port);

        System.out.println("Client sale request started");

        ObjectOutputStream out = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream in = new ObjectInputStream(socket.getInputStream());

        out.writeObject(new SaleRequest(showId, seatIds));

        Object response = in.readObject();

        if (response instanceof SaleError) {
            SaleError saleError = (SaleError) response;
            System.out.printf("Server responded with sale error %s\n", saleError.toString());
        } else if (response instanceof SaleResponse) {
            SaleResponse saleResponse = (SaleResponse) response;
            System.out.printf("Server responded with sale response %s\n", saleResponse.toString());
        } else if (response instanceof  StatusResponse) {
            StatusResponse statusResponse = (StatusResponse) response;
            System.out.printf("Server responded with status %s\n", statusResponse.toString());
            return false;
        }

        return true;
    }

    public static final int maxNumberOfSeatsToSell = 5;

    public void run(String host, int port) throws IOException, ClassNotFoundException, InterruptedException {
        this.host = host;
        this.port = port;

        shows = doShowsRequest();
        if (shows.size() == 0) {
            return;
        }

        while (true) {
            Random randomizer = new Random();
            System.out.println(shows.size());
            Show show = shows.get(randomizer.nextInt(shows.size()));
            int noSeatsToSell = randomizer.nextInt(maxNumberOfSeatsToSell);

            ArrayList<Integer> seatsIds = new ArrayList<>();
            for (int i = 0; i < noSeatsToSell; i++) {
                int seatId = randomizer.nextInt(show.noSeats);
                seatsIds.add(seatId);
            }

            boolean success = doSaleRequest(show.id, seatsIds);
            if (!success) {
                return;
            }


            Thread.sleep(2000);
        }
    }
}

public class MainClient {
    public static void main(String[] args) {
        System.out.println("Hello world from client");

        Client client = new Client();
        try {
            client.run("localhost", 8080);
        } catch (IOException | ClassNotFoundException | InterruptedException e) {
            e.printStackTrace();
        }
    }
}
