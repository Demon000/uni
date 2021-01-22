public class Transaction {
    public int userId;
    public TransactionType transactionType;
    public CurrencyType currencyType;
    public int sum;
    public int sold;

    public Transaction(int userId, TransactionType transactionType, CurrencyType currencyType, int sum) {
        this.userId = userId;
        this.transactionType = transactionType;
        this.currencyType = currencyType;
        this.sum = sum;
    }

    @Override
    public String toString() {
        return "Transaction{" +
                "userId=" + userId +
                ", transactionType=" + transactionType +
                ", currencyType=" + currencyType +
                ", sum=" + sum +
                ", sold=" + sold +
                '}';
    }
}
