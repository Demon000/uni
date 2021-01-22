import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class Parking {
    private final List<ParkingTransaction> transactions = Collections.synchronizedList(new ArrayList<>());
    private final AtomicInteger noOccupiedSpaces = new AtomicInteger(0);
    private final AtomicInteger noConnections;
    private final BlockingQueue<ParkingTransaction> incomingTransactions;
    private final ParkingWorker parkingWorker;
    int noTotalSpaces;

    public Parking(int noTotalSpaces, int noOccupiedSpaces, int noConnections) {
        this.noTotalSpaces = noTotalSpaces;
        this.noConnections = new AtomicInteger(noConnections);

        incomingTransactions = new LinkedBlockingQueue<>(noTotalSpaces);

        while (noOccupiedSpaces > 0) {
            entry();
            noOccupiedSpaces--;
        }

        parkingWorker = new ParkingWorker();
        parkingWorker.start();
    }

    public class ParkingWorker extends Thread {
        @Override
        public void run() {
            while (true) {
                ParkingTransaction transaction;

                try {
                    transaction = incomingTransactions.take();
                } catch (InterruptedException e) {
                    break;
                }

                if (transaction.transactionType == ParkingTransactionType.ENTRY) {
                    noOccupiedSpaces.incrementAndGet();
                } else {
                    noOccupiedSpaces.decrementAndGet();
                }

                transactions.add(transaction);
            }
        }
    }

    public void endConnection() {
        noConnections.decrementAndGet();
    }

    public boolean allConnectionsEnded() {
        return noConnections.get() == 0;
    }

    public void entry() {
        incomingTransactions.add(new ParkingTransaction(ParkingTransactionType.ENTRY));
    }

    public void exit() {
        incomingTransactions.add(new ParkingTransaction(ParkingTransactionType.EXIT));
    }

    public AvailableSpacesData getAvailableSpacesData() {
        List<ParkingTransaction> localTransactions = new ArrayList<>(transactions);
        int counter = 0;

        for (ParkingTransaction transaction : localTransactions) {
            if (transaction.transactionType == ParkingTransactionType.ENTRY) {
                counter++;
            } else {
                counter--;
            }
        }

        return new AvailableSpacesData(noTotalSpaces - counter, localTransactions);
    }
}
