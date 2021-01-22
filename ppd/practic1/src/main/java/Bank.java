import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

public class Bank {
    private final List<Transaction> transactions = Collections.synchronizedList(new ArrayList<>());
    private final AtomicInteger soldRON = new AtomicInteger(0);
    private final AtomicInteger soldEUR = new AtomicInteger(0);

    private final AtomicInteger lastNotifiedSize = new AtomicInteger(0);
    private final AtomicInteger numberOfConnections;
    private final int notifyAt;
    public final Object transactionsNotifier = new Object();

    public Bank(int notifyAt, int numberOfConnections) {
        this.numberOfConnections = new AtomicInteger(numberOfConnections);
        this.notifyAt = notifyAt;
    }

    void notifyTransactions() {
        synchronized (transactionsNotifier) {
            transactionsNotifier.notifyAll();
        }
    }

    void waitForTransactionsNotification() throws InterruptedException {
        synchronized (transactionsNotifier) {
            transactionsNotifier.wait();
        }
    }

    void endConnection() {
        int connections = numberOfConnections.decrementAndGet();
        if (connections == 0) {
            this.notifyTransactions();
        }
    }

    boolean allConnectionsClosed() {
        return numberOfConnections.get() == 0;
    }

    void addTransaction(Transaction transaction) throws BankException {
        int sum;

        if (transaction.transactionType == TransactionType.WITHDRAWAL) {
            sum = -transaction.sum;
        } else if (transaction.transactionType == TransactionType.DEPOSIT) {
            sum = transaction.sum;
        } else {
            throw new RuntimeException("Invalid transaction type");
        }

        AtomicInteger sold;
        if (transaction.currencyType == CurrencyType.RON) {
            sold = soldRON;
        } else if (transaction.currencyType == CurrencyType.EUR) {
            sold = soldEUR;
        } else {
            throw new RuntimeException("Invalid currency type");
        }

        int newSold = sold.addAndGet(sum);

        if (newSold < 0 && sum < 0) {
            sold.addAndGet(-sum);
            throw new BankException("Failed to add transaction, sold less than 0", transaction);
        }

        transaction.sold = newSold;

        transactions.add(transaction);

        int newNotifiedSize = transactions.size();
        int oldNotifiedSize = lastNotifiedSize.get();
        if (newNotifiedSize - oldNotifiedSize >= notifyAt) {
            lastNotifiedSize.addAndGet(newNotifiedSize - oldNotifiedSize);
            notifyTransactions();
        }
    }

    List<Transaction> getTransactions() {
        return new ArrayList<>(transactions);
    }

    void depositRON(int userId, int sum) throws BankException {
        Transaction transaction = new Transaction(userId, TransactionType.DEPOSIT, CurrencyType.RON, sum);
        this.addTransaction(transaction);
    }

    void withdrawRON(int userId, int sum) throws BankException {
        Transaction transaction = new Transaction(userId, TransactionType.WITHDRAWAL, CurrencyType.RON, sum);
        this.addTransaction(transaction);
    }

    void depositEUR(int userId, int sum) throws BankException {
        Transaction transaction = new Transaction(userId, TransactionType.DEPOSIT, CurrencyType.EUR, sum);
        this.addTransaction(transaction);
    }

    void withdrawEUR(int userId, int sum) throws BankException {
        Transaction transaction = new Transaction(userId, TransactionType.WITHDRAWAL, CurrencyType.EUR, sum);
        this.addTransaction(transaction);
    }
}
