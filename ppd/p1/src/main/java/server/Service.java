package server;

import common.CheckError;
import common.Sale;
import common.SaleError;
import common.Show;

import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicInteger;

public class Service {
    private static final AtomicInteger showIdCounter = new AtomicInteger(0);
    ArrayList<Show> shows = new ArrayList<>();

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


        int id = saleIdCounter.incrementAndGet();
        int sum = show.price * soldSeatIds.size();
        Sale sale = new Sale(id, showId, sum, seatIds);
        sales.add(sale);

        show.sum += sum;
        show.soldSeatIds.addAll(seatIds);

        return sale;
    }

    synchronized public void checkConsistency() throws CheckError {
        ArrayList<Show> shows = getShows();

        for (Show show : shows) {
            int salesSum = getSoldSeatsSumForShowId(show.id);

            if (salesSum != show.sum) {
                throw new CheckError("Show sum doesn't match sum of sales");
            }

            ArrayList<Integer> showSoldSeatIds = new ArrayList<>(show.soldSeatIds);
            ArrayList<Integer> salesSoldSeatIds = getSoldSeatsForShowId(show.id);

            salesSoldSeatIds.sort(Integer::compareTo);
            showSoldSeatIds.sort(Integer::compareTo);

            if (!showSoldSeatIds.equals(salesSoldSeatIds)) {
                throw new CheckError("Show sold seat ids doesn't match sales sold seat ids");
            }
        }
    }
}
