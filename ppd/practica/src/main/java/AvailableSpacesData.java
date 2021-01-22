import java.util.List;

public class AvailableSpacesData {
    public final int noAvailableSpaces;
    public final List<ParkingTransaction> transactions;

    public AvailableSpacesData(int noAvailableSpaces, List<ParkingTransaction> transactions) {
        this.noAvailableSpaces = noAvailableSpaces;
        this.transactions = transactions;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Transactions:\n");

        for (ParkingTransaction transaction : transactions) {
            sb.append(transaction.toString());
            sb.append('\n');
        }

        sb.append("Available spaces: ");
        sb.append(noAvailableSpaces);
        sb.append('\n');

        return sb.toString();
    }
}
