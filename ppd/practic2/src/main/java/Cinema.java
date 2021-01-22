import java.util.*;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class Cinema {
    private final AtomicInteger numberOfConnections;

    public Map<Integer, Hall> halls = Collections.synchronizedMap(new HashMap<>());
    public final BlockingQueue<Reservation> failedReservations = new LinkedBlockingQueue<>();

    public Cinema(int numberOfConnections) {
        this.numberOfConnections = new AtomicInteger(numberOfConnections);
    }

    void endConnection() {
        int connections = numberOfConnections.decrementAndGet();
        if (connections == 0) {
            this.notifyFailedReservation(null);
        }
    }

    boolean allConnectionsClosed() {
        return numberOfConnections.get() == 0;
    }

    public void addHall(Hall hall) {
        halls.put(hall.id, hall);
    }

    public void notifyFailedReservation(Reservation reservation) {
        synchronized (failedReservations) {
            if (reservation != null) {
                failedReservations.add(reservation);
            }

            failedReservations.notifyAll();
        }
    }

    public boolean hasFailedReservations() {
        return !failedReservations.isEmpty();
    }

    public void waitForFailedReservation() throws InterruptedException {
        synchronized (failedReservations) {
            failedReservations.wait();
        }
    }

    public Reservation getFailedReservation() throws InterruptedException {
        return failedReservations.take();
    }

    public void reserve(Reservation reservation) {
        Hall hall = halls.get(reservation.hallId);
        if (hall == null) {
            throw new RuntimeException("Invalid hall id");
        }

        synchronized (hall) {
            boolean success = hall.reserveSeat(reservation.seatRowId, reservation.seatId);
            if (!success) {
                notifyFailedReservation(reservation);
            }
        }
    }

    public String getHallsString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Halls:\n");

        for (Hall hall : halls.values()) {
            synchronized (hall) {
                sb.append(hall.toString());
                sb.append('\n');
            }
        }

        return sb.toString();
    }

    public Collection<Hall> getHalls() {
        return halls.values();
    }

    public Hall getHallById(int hallId) {
        return halls.get(hallId);
    }
}
