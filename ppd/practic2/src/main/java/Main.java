import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Main {
    public static int NO_WORKER_THREADS = 2;
    public static int RESERVATION_INTERVAL_MS = 1000;
    public static int PRINT_INTERVAL_MS = 3000;
    public static int NO_HALLS = 3;
    public static int NO_MIN_ROWS = 3;
    public static int NO_MAX_ROWS = 5;
    public static int NO_MIN_SEATS = 5;
    public static int NO_MAX_SEATS = 7;
    public static int NO_RESERVATIONS = 100;
    public static Random random = new Random();

    static class ErrorThread extends Thread {
        private Cinema cinema;

        public ErrorThread(Cinema cinema) {
            this.cinema = cinema;
        }

        @Override
        public void run() {
            while (true) {
                try {
                    Reservation reservation = cinema.waitForFailedReservation();
                    if (cinema.allConnectionsClosed()) {
                        break;
                    }

                    System.out.printf("Failed %s\n", reservation);
                } catch (InterruptedException e) {
                    break;
                }
            }
        }
    }

    static class PrinterThread extends Thread {
        private Cinema cinema;

        public PrinterThread(Cinema cinema) {
            this.cinema = cinema;
        }

        @Override
        public void run() {
            while (true) {
                if (cinema.allConnectionsClosed()) {
                    break;
                }

                System.out.println(cinema.getHallsString());

                try {
                    sleep(PRINT_INTERVAL_MS);
                } catch (InterruptedException e) {
                    break;
                }
            }
        }
    }

    static class WorkerThread extends Thread {
        private Cinema cinema;
        private List<Reservation> reservations;

        public WorkerThread(Cinema cinema, List<Reservation> reservations) {
            this.cinema = cinema;
            this.reservations = reservations;
        }

        @Override
        public void run() {
            for (Reservation reservation : reservations) {
                cinema.reserve(reservation);

                try {
                    sleep(RESERVATION_INTERVAL_MS);
                } catch (InterruptedException e) {
                    break;
                }
            }

            cinema.endConnection();
        }
    }

    public static int getRandomNumber(int min, int max) {
        return random.nextInt(max - min) + min;
    }

    public static void main(String[] args) {
        Cinema cinema = new Cinema(NO_WORKER_THREADS);

        for (int i = 0; i < NO_HALLS; i++) {
            int noRows = getRandomNumber(NO_MIN_ROWS, NO_MAX_ROWS);
            int noSeats = getRandomNumber(NO_MIN_SEATS, NO_MAX_SEATS);

            Hall hall = new Hall(i, noRows, noSeats);
            cinema.addHall(hall);
        }

        List<Reservation> reservations = new ArrayList<>();
        for (int i = 0; i < NO_RESERVATIONS; i++) {
            int hallId = getRandomNumber(0, NO_HALLS);
            Hall hall = cinema.getHallById(hallId);
            int rowId = getRandomNumber(0, hall.noRows);
            int seatId = getRandomNumber(0, hall.noSeats);
            reservations.add(new Reservation(hallId, rowId, seatId));
        }

        PrinterThread printerThread = new PrinterThread(cinema);
        printerThread.start();

        ErrorThread errorThread = new ErrorThread(cinema);
        errorThread.start();

        int chunk = NO_RESERVATIONS / NO_WORKER_THREADS;
        int rest = NO_RESERVATIONS % NO_WORKER_THREADS;
        int start;
        int end = 0;
        for (int i = 0; i < NO_WORKER_THREADS; i++) {
            start = end;
            end = start + chunk;

            if (end > NO_RESERVATIONS) {
                end = NO_RESERVATIONS;
            }

            if (rest > 0) {
                end += 1;
                rest--;
            }

            System.out.printf("thread: %d, start: %d, end: %d%n", i, start, end);
            List<Reservation> workerThreadReservations = reservations.subList(start, end);
            WorkerThread workerThread = new WorkerThread(cinema, workerThreadReservations);
            workerThread.start();
        }
    }
}
