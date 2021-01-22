public class ParkingTransaction {
    public ParkingTransactionType transactionType;

    public ParkingTransaction(ParkingTransactionType transactionType) {
        this.transactionType = transactionType;
    }

    @Override
    public String toString() {
        return "ParkingTransaction{" +
                "transactionType=" + transactionType +
                '}';
    }
}
