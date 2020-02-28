package domain;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.concurrent.atomic.AtomicInteger;

public class Order extends BaseEntity<Integer> {
    static final AtomicInteger NEXT_ID = new AtomicInteger(0);
    static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");

    private final int roomNumber;
    private final String productName;
    private final float productPrice;
    private final LocalDateTime time;

    public Order(int roomNumber, String productName, float productPrice, LocalDateTime time) {
        super(NEXT_ID.getAndIncrement());

        this.roomNumber = roomNumber;
        this.productName = productName;
        this.productPrice = productPrice;
        this.time = time;
    }

    public int getRoomNumber() {
        return roomNumber;
    }

    public String getProductName() {
        return productName;
    }

    public float getProductPrice() {
        return productPrice;
    }

    public LocalDateTime getTime() {
        return time;
    }
}
