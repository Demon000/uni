import java.util.*;

public class Main {
    public static int NO_TRANSACTIONS_PER_THREAD = 20;
    public static int NO_THREADS = 3;
    public static int NOTIFY_AT_NO_TRANSACTIONS = 5;
    public static int THREAD_TRANSACTION_INTERVAL_MS = 1000;

    public static class BankWorkerThread extends Thread {
        private final Random random = new Random();
        private final Bank bank;

        private final int MIN_SUM = 1;
        private final int MAX_SUM = 1000;

        private int transactionsToDo;

        public BankWorkerThread(Bank bank, int transactionsToDo) {
            this.bank = bank;
            this.transactionsToDo = transactionsToDo;
        }

        private CurrencyType getRandomCurrencyType() {
            List<CurrencyType> currencyTypes = List.of(CurrencyType.values());
            int size = currencyTypes.size();
            return currencyTypes.get(random.nextInt(size));
        }

        private TransactionType getRandomTransactionType() {
            List<TransactionType> transactionTypes = List.of(TransactionType.values());
            int size = transactionTypes.size();
            return transactionTypes.get(random.nextInt(size));
        }

        private int getRandomNumber(int min, int max) {
            return random.nextInt(max - min) + min;
        }

        @Override
        public void run() {
            while (transactionsToDo > 0) {
                CurrencyType currencyType = this.getRandomCurrencyType();
                TransactionType transactionType = this.getRandomTransactionType();
                int sum = getRandomNumber(MIN_SUM, MAX_SUM);
                int userId = (int) Thread.currentThread().getId();

                try {
                    if (currencyType == CurrencyType.RON) {
                        if (transactionType == TransactionType.WITHDRAWAL) {
                            bank.withdrawRON(userId, sum);
                        } else if (transactionType == TransactionType.DEPOSIT) {
                            bank.depositRON(userId, sum);
                        }
                    } else if (currencyType == CurrencyType.EUR) {
                        if (transactionType == TransactionType.WITHDRAWAL) {
                            bank.withdrawEUR(userId, sum);
                        } else if (transactionType == TransactionType.DEPOSIT) {
                            bank.depositEUR(userId, sum);
                        }
                    }
                } catch (BankException e) {
                    System.out.println(e);
                    System.out.println();
                }

                transactionsToDo--;

                try {
                    sleep(THREAD_TRANSACTION_INTERVAL_MS);
                } catch (InterruptedException e) {
                    break;
                }
            }

            bank.endConnection();
        }
    }

    public static class BankPrinterThread extends Thread {
        private Bank bank;

        public BankPrinterThread(Bank bank) {
            this.bank = bank;
        }

        @Override
        public void run() {
            while (true) {
                try {
                    this.bank.waitForTransactionsNotification();
                } catch (InterruptedException e) {
                    break;
                }

                List<Transaction> transactions = bank.getTransactions();

                System.out.println("Transactions: ");
                for (Transaction transaction : transactions) {
                    System.out.println(transaction);
                }

                System.out.println();

                if (this.bank.allConnectionsClosed()) {
                    break;
                }
            }
        }
    }

    public static void main(String[] args) {
        Bank bank = new Bank(NOTIFY_AT_NO_TRANSACTIONS, NO_THREADS);
        BankPrinterThread printerThread = new BankPrinterThread(bank);
        printerThread.start();

        for (int i = 0; i < NO_THREADS; i++) {
            BankWorkerThread workerThread = new BankWorkerThread(bank, NO_TRANSACTIONS_PER_THREAD);
            workerThread.start();
        }

    }
}
