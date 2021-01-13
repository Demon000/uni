package server;

import common.CheckError;
import common.Sale;
import common.SaleError;
import common.Show;

import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class Service {
    private static final AtomicInteger showIdCounter = new AtomicInteger(0);
    ArrayList<Show> shows = new ArrayList<>();
    private FileWriter writer;

    public Service(FileWriter writer) {
        this.writer = writer;
    }

    synchronized public Show createShow(String title, int price, int noSeats) {
        int id = showIdCounter.incrementAndGet();
        Show show = new Show(id, title, price, noSeats);
        shows.add(show);
        return show;
    }

    synchronized public ArrayList<Show> getShows() {
        return shows;
    }

    synchronized public Show getShowById(int showId) {
        for (Show show : getShows()) {
            if (show.id == showId) {
                return show;
            }
        }

        return null;
    }

    private static final AtomicInteger saleIdCounter = new AtomicInteger(0);
    public ArrayList<Sale> sales = new ArrayList<>();

    synchronized public ArrayList<Sale> getSales() {
        return sales;
    }

    synchronized public ArrayList<Sale> getSalesForShowId(int showId) {
        ArrayList<Sale> salesForShowId = new ArrayList<>();

        for (Sale sale : getSales()) {
            if (sale.showId == showId) {
                salesForShowId.add(sale);
            }
        }

        return salesForShowId;
    }

    synchronized public ArrayList<Integer> getSoldSeatsForShowId(int showId) {
        ArrayList<Sale> salesForShowId = getSalesForShowId(showId);
        ArrayList<Integer> soldSeatIds = new ArrayList<>();

        for (Sale sale : salesForShowId) {
            soldSeatIds.addAll(sale.soldSeatIds);
        }

        return soldSeatIds;
    }

    synchronized public int getSoldSeatsSumForShowId(int showId) {
        ArrayList<Sale> salesForShowId = getSalesForShowId(showId);
        int sum = 0;

        for (Sale sale : salesForShowId) {
            sum += sale.sum;
        }

        return sum;
    }

    synchronized public Sale createSale(int showId, ArrayList<Integer> seatIds) throws SaleError {
        Show show = getShowById(showId);
        if (show == null) {
            throw new SaleError("Failed to find show with id");
        }

        ArrayList<Integer> soldSeatIds = getSoldSeatsForShowId(showId);

        for (int seatId : seatIds) {
            if (seatId >= show.noSeats) {
                throw new SaleError(String.format("Invalid seat id %d bigger than " +
                        "number of seats %d", seatId, show.noSeats));
            }

            if (soldSeatIds.contains(seatId)) {
                throw new SaleError(String.format("Invalid seat id %d already bought", seatId));
            }
        }

        int sum = show.price * seatIds.size();

        int id = saleIdCounter.incrementAndGet();
        Sale sale = new Sale(id, showId, sum, seatIds);
        sales.add(sale);

        show.soldSeatIds.addAll(seatIds);
        show.sum += sum;

        return sale;
    }

    synchronized public void checkConsistency() throws IOException {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yy HH-mm-ss");
        Date date = new Date();
        boolean correct = true;

        StringBuilder sb = new StringBuilder();

        sb.append(dateFormat.format(date));
        sb.append("\n");

        ArrayList<Show> shows = getShows();

        for (Show show : shows) {
            sb.append(show.title);
            sb.append(" ");

            sb.append(show.id);
            sb.append(" ");

            sb.append(show.sum);
            sb.append(" ");

            String soldSeatIdsStr = show.soldSeatIds
                    .stream()
                    .map(Object::toString)
                    .collect(Collectors.joining(", "));

            sb.append(soldSeatIdsStr);

            int salesSum = getSoldSeatsSumForShowId(show.id);
            if (salesSum != show.sum) {
                correct = false;
            }

            ArrayList<Integer> showSoldSeatIds = new ArrayList<>(show.soldSeatIds);
            ArrayList<Integer> salesSoldSeatIds = getSoldSeatsForShowId(show.id);

            salesSoldSeatIds.sort(Integer::compareTo);
            showSoldSeatIds.sort(Integer::compareTo);

            if (!showSoldSeatIds.equals(salesSoldSeatIds)) {
                correct = false;
            }

            sb.append("\n");
        }

        sb.append(correct ? "corect" : "incorect");

        sb.append("\n");
        writer.write(sb.toString());
        writer.flush();
    }
}
