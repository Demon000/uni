import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class Parking {
    private final List<ParkingTransaction> transactions = Collections.synchronizedList(new ArrayList<>());
    private final AtomicInteger noOccupiedSpaces = new AtomicInteger(0);
    int noTotalSpaces;

    public Parking(int noTotalSpaces, int noOccupiedSpaces) {
        this.noTotalSpaces = noTotalSpaces;

        while (noOccupiedSpaces > 0) {
            entry();
            noOccupiedSpaces--;
        }
    }

    public boolean entry() {
        if (noOccupiedSpaces.incrementAndGet() > noTotalSpaces) {
            noOccupiedSpaces.decrementAndGet();
            return false;
        }

        transactions.add(new ParkingTransaction(ParkingTransactionType.ENTRY));
        return true;
    }

    public boolean exit() {
        if (noOccupiedSpaces.decrementAndGet() < 0) {
            noOccupiedSpaces.incrementAndGet();
            return false;
        }

        transactions.add(new ParkingTransaction(ParkingTransactionType.EXIT));
        return true;
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
