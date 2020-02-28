package domain;

import java.time.LocalDateTime;

public class OrderStringSerializer implements ISerializer<Integer, Order, String> {
    @Override
    public String serialize(Order order) {
        String dateString = Order.FORMATTER.format(order.getTime());
        return String.format("%d\t%s\t%f\t%s", order.getRoomNumber(), order.getProductName(), order.getProductPrice(), dateString);
    }

    @Override
    public Order deserialize(String line) {
        String[] parts = line.split("\\t");
        int roomId = Integer.parseInt(parts[0]);
        String productName = parts[1];
        float price = Float.parseFloat(parts[2]);
        LocalDateTime time = LocalDateTime.parse(parts[3], Order.FORMATTER);

        return new Order(roomId, productName, price, time);
    }
}
