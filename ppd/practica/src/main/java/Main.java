public class Main {
    public static class WorkerThread extends Thread {
        private Parking parking;
        private final ParkingTransactionType transactionType;
        private int totalCount;
        private final int countPerIteration;
        private final int iterationTime;

        public WorkerThread(Parking parking,
                            ParkingTransactionType transactionType,
                            int totalCount,
                            int countPerIteration,
                            int iterationTime) {
            this.parking = parking;
            this.transactionType = transactionType;
            this.totalCount = totalCount;
            this.countPerIteration = countPerIteration;
            this.iterationTime = iterationTime;
        }

        @Override
        public void run() {
            for (int i = 0; i < totalCount; i++) {
                for (int j = 0; j < countPerIteration; j++) {
                    if (transactionType == ParkingTransactionType.ENTRY) {
                        parking.entry();
                    } else if (transactionType == ParkingTransactionType.EXIT) {
                        parking.exit();
                    } else {
                        throw new RuntimeException("Invalid transaction type");
                    }
                }

                try {
                    sleep(iterationTime);
                } catch (InterruptedException e) {
                    return;
                }
            }

            parking.endConnection();
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

                if (parking.allConnectionsEnded()) {
                    return;
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

    public static int NO_TOTAL_ENTRIES_PER_THREAD = 200;
    public static int NO_TOTAL_EXITS_PER_THREAD = 275;
    public static int NO_ENTRIES_PER_ITERATION = 1;
    public static int NO_EXITS_PER_ITERATION = 1;

    public static int ENTRY_ITERATION_TIME_MS = 20;
    public static int EXIT_ITERATION_TIME_MS = 15;
    public static int PRINTER_ITERATION_TIME_MS = 5;

    public static void main(String[] args) {
        Parking parking = new Parking(NO_TOTAL_PARKING_PLACES, NO_INITIAL_OCCUPIED_PARKING_PLACES,
                NO_WORKER_THREADS_ENTRY + NO_WORKER_THREADS_EXIT);
        PrinterThread printerThread = new PrinterThread(parking, PRINTER_ITERATION_TIME_MS);
        printerThread.start();

        for (int i = 0; i < NO_WORKER_THREADS_ENTRY; i++) {
            WorkerThread workerThread = new WorkerThread(parking, ParkingTransactionType.ENTRY,
                    NO_TOTAL_ENTRIES_PER_THREAD, NO_ENTRIES_PER_ITERATION, ENTRY_ITERATION_TIME_MS);
            workerThread.start();
        }

        for (int i = 0; i < NO_WORKER_THREADS_EXIT; i++) {
            WorkerThread workerThread = new WorkerThread(parking, ParkingTransactionType.EXIT,
                    NO_TOTAL_EXITS_PER_THREAD, NO_EXITS_PER_ITERATION, EXIT_ITERATION_TIME_MS);
            workerThread.start();
        }
    }
}
