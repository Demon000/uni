import java.util.ArrayList;
import java.util.List;

public class Hall {
    int id;
    int noRows;
    int noSeats;
    List<List<Boolean>> seats;

    public Hall(int id, int noRows, int noSeats) {
        this.id = id;
        this.noRows = noRows;
        this.noSeats = noSeats;
        this.seats = new ArrayList<>();

        for (int i = 0; i < noRows; i++) {
            this.seats.add(new ArrayList<>());

            for (int j = 0; j < noSeats; j++) {
                this.seats.get(i).add(false);
            }
        }
    }

    boolean reserveSeat(int rowId, int seatId) {
        if (seats.size() <= rowId) {
            return false;
        }

        if (seats.get(rowId).size() < seatId) {
            return false;
        }

        if (seats.get(rowId).get(seatId)) {
            return false;
        }

        seats.get(rowId).set(seatId, true);

        return true;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder()
                .append("Hall{")
                .append("id=")
                .append(id)
                .append(", noRows=")
                .append(noRows)
                .append(", noSeats=")
                .append(noSeats)
                .append(", seats=");

        for (int i = 0; i < noRows; i++) {
            sb.append('\n');
            for (int j = 0; j < noSeats; j++) {
                boolean reserved = this.seats.get(i).get(j);
                if (reserved) {
                    sb.append('X');
                } else {
                    sb.append('O');
                }
            }
        }

        sb.append('}');

        return sb.toString();
    }
}
