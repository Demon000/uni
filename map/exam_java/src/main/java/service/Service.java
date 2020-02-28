package service;

import domain.Order;
import domain.Product;
import domain.Room;
import observer.Observable;
import repository.IRepository;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

import static utils.CollectionUtils.listFromIterable;
import static utils.CollectionUtils.streamFromIterable;

public class Service extends Observable {
    private final IRepository<Integer, Room> roomsRepository;
    private final IRepository<String, Product> productsRepository ;
    private final IRepository<Integer, Order> pendingOrdersRepository;
    private final IRepository<Integer, Order> completedOrdersRepository;

    public Service(IRepository<Integer, Room> roomsRepository,
                   IRepository<String, Product> productsRepository,
                   IRepository<Integer, Order> pendingOrdersRepository,
                   IRepository<Integer, Order> completedOrdersRepository) {
        this.roomsRepository = roomsRepository;
        this.productsRepository = productsRepository;
        this.pendingOrdersRepository = pendingOrdersRepository;
        this.completedOrdersRepository = completedOrdersRepository;
    }

    public void addProduct(String productName, float productPrice) {
        Product existing = productsRepository.find(productName);
        if (existing != null) {
            return;
        }

        Product product = new Product(productName, productPrice);
        productsRepository.add(product);
        change(ServiceObserverKeys.PRODUCT_ADDED, null, product);
    }

    public List<Product> getProducts() {
        return listFromIterable(productsRepository.find());
    }

    public void orderProduct(Room room, Product product) {
        Order order = new Order(room.getNumber(), product.getName(), product.getPrice(), LocalDateTime.now());
        pendingOrdersRepository.add(order);
        change(ServiceObserverKeys.PRODUCT_ORDERED, null, order);
    }

    public List<Order> getCompletedRoomOrders(Room room) {
        return streamFromIterable(completedOrdersRepository.find())
                .filter(order -> order.getRoomNumber() == room.getNumber())
                .collect(Collectors.toList());
    }

    public float getRoomOrdersSum(Room room) {
        return getCompletedRoomOrders(room)
                .stream()
                .map(Order::getProductPrice)
                .reduce(0.0f, Float::sum);
    }

    public void completeOrder(Order order) {
        completedOrdersRepository.add(order);
        pendingOrdersRepository.remove(order.getId());
        change(ServiceObserverKeys.ORDER_COMPLETED, null, order);
    }

    public List<Room> getRooms() {
        return listFromIterable(roomsRepository.find());
    }
}
