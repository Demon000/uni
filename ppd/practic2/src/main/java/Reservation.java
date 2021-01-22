public class Reservation {
    int hallId;
    int seatRowId;
    int seatId;

    public Reservation() {}

    public Reservation(int hallId, int seatRowId, int seatId) {
        this.hallId = hallId;
        this.seatRowId = seatRowId;
        this.seatId = seatId;
    }

    public void setAll(Reservation reservation) {
        this.hallId = reservation.hallId;
        this.seatRowId = reservation.seatRowId;
        this.seatId = reservation.seatId;
    }

    @Override
    public String toString() {
        return "Reservation{" +
                "hallId=" + hallId +
                ", seatRowId=" + seatRowId +
                ", seatId=" + seatId +
                '}';
    }
}
