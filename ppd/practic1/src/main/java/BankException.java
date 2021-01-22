public class BankException extends Exception {
    private Transaction transaction;

    public BankException(String message, Transaction transaction) {
        super(message);
        this.transaction = transaction;
    }

    @Override
    public String toString() {
        return super.getMessage() + " " + transaction.toString();
    }
}
