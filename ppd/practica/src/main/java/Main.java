public class Main {
    public static class WorkerThread extends Thread {
        private Parking parking;
        private final ParkingTransactionType transactionType;
        private final int countPerIteration;
        private final int iterationTime;

        public WorkerThread(Parking parking,
                            ParkingTransactionType transactionType,
                            int countPerIteration, int iterationTime) {
            this.parking = parking;
            this.transactionType = transactionType;
            this.countPerIteration = countPerIteration;
            this.iterationTime = iterationTime;
        }

        @Override
        public void run() {
            while (true) {
                for (int i = 0; i < countPerIteration; i++) {
                    boolean result;

                    if (transactionType == ParkingTransactionType.ENTRY) {
                        result = parking.entry();
                    } else if (transactionType == ParkingTransactionType.EXIT) {
                        result = parking.exit();
                    } else {
                        throw new RuntimeException("Invalid transaction type");
                    }

                    if (!result) {
                        System.out.println("Failed to add transaction");
                    }
                }

                try {
                    sleep(iterationTime);
                } catch (InterruptedException e) {
                    break;
                }
            }
        }
    }

    public static class PrinterThread extends Thread {
        private Parking parking;
        private final int iterationTime;

        public PrinterThread(Parking parking, int iterationTime) {
            this.parking = parking;
            this.iterationTime = iterationTime;
        }

        @Override
        public void run() {
            while (true) {
                AvailableSpacesData data = parking.getAvailableSpacesData();

                System.out.println(data);

                try {
                    sleep(iterationTime);
                } catch (InterruptedException e) {
                    break;
                }
            }
        }
    }

//    public static int NO_WORKER_THREADS_ENTRY = 3;
//    public static int NO_WORKER_THREADS_EXIT = 2;
//
//    public static int NO_INITIAL_OCCUPIED_PARKING_PLACES = 25;
//    public static int NO_TOTAL_PARKING_PLACES = 100;
//
//    public static int NO_ENTRIES_PER_ITERATION = 200;
//    public static int NO_EXITS_PER_ITERATION = 275;
//
//    public static int ENTRY_ITERATION_TIME_MS = 20;
//    public static int EXIT_ITERATION_TIME_MS = 15;
//    public static int PRINTER_ITERATION_TIME_MS = 5;

    public static int NO_WORKER_THREADS_ENTRY = 3;
    public static int NO_WORKER_THREADS_EXIT = 2;

    public static int NO_INITIAL_OCCUPIED_PARKING_PLACES = 25;
    public static int NO_TOTAL_PARKING_PLACES = 100;

    public static int NO_ENTRIES_PER_ITERATION = 1;
    public static int NO_EXITS_PER_ITERATION = 1;

    public static int ENTRY_ITERATION_TIME_MS = 20;
    public static int EXIT_ITERATION_TIME_MS = 15;
    public static int PRINTER_ITERATION_TIME_MS = 5;

    public static void main(String[] args) {
        Parking parking = new Parking(NO_TOTAL_PARKING_PLACES, NO_INITIAL_OCCUPIED_PARKING_PLACES);
        PrinterThread printerThread = new PrinterThread(parking, PRINTER_ITERATION_TIME_MS);
        printerThread.start();

        for (int i = 0; i < NO_WORKER_THREADS_ENTRY; i++) {
            WorkerThread workerThread = new WorkerThread(parking, ParkingTransactionType.ENTRY,
                    NO_ENTRIES_PER_ITERATION, ENTRY_ITERATION_TIME_MS);
            workerThread.start();
        }

        for (int i = 0; i < NO_WORKER_THREADS_EXIT; i++) {
            WorkerThread workerThread = new WorkerThread(parking, ParkingTransactionType.EXIT,
                    NO_EXITS_PER_ITERATION, EXIT_ITERATION_TIME_MS);
            workerThread.start();
        }    }
}
