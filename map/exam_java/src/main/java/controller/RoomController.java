package controller;

import domain.Order;
import domain.Product;
import domain.Room;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;
import observer.Observer;
import service.Service;
import service.ServiceObserverKeys;

import java.time.LocalDateTime;
import java.util.List;

public class RoomController implements Observer {
    public static final String VIEW_NAME = "/RoomView.fxml";
    public static final String VIEW_TITLE = "Room window";
    public static final String VIEW_TITLE_FORMAT = "Room %d window";

    private Service service;
    private Room room;

    @FXML
    private TableView<Product> productsTable;

    @FXML
    private TableColumn<Product, String> productNameColumn;

    @FXML
    private TableColumn<Product, Float> productPriceColumn;

    @FXML
    private TableView<Order> ordersTable;

    @FXML
    private TableColumn<Order, String> orderProductNameColumn;

    @FXML
    private TableColumn<Order, Float> orderProductPriceColumn;

    @FXML
    private TableColumn<Order, LocalDateTime> orderTimeColumn;

    @FXML
    private Label totalField;

    public RoomController(Service service, Room room) {
        this.service = service;
        this.room = room;
    }

    private void loadProductsTable() {
        productsTable.getItems().setAll(service.getProducts());
    }

    @FXML
    public void initialize() {
        productNameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        productPriceColumn.setCellValueFactory(new PropertyValueFactory<>("price"));
        productsTable.getSelectionModel().setSelectionMode(SelectionMode.MULTIPLE);
        loadProductsTable();

        orderProductNameColumn.setCellValueFactory(new PropertyValueFactory<>("productName"));
        orderProductPriceColumn.setCellValueFactory(new PropertyValueFactory<>("productPrice"));
        orderTimeColumn.setCellValueFactory(new PropertyValueFactory<>("time"));

        updateTotal();
        service.addObserver(this);
    }

    private List<Product> getSelectedProducts() {
        return productsTable.getSelectionModel().getSelectedItems();
    }

    private void updateTotal() {
        float total = service.getRoomOrdersSum(room);
        totalField.setText(String.valueOf(total));
    }

    @FXML
    void onOrderProductButtonPress(ActionEvent event) {
        List<Product> products = getSelectedProducts();
        for (Product product : products) {
            service.orderProduct(room, product);
        }
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        if (key.equals(ServiceObserverKeys.PRODUCT_ADDED)) {
            Product product = (Product) newValue;
            productsTable.getItems().add(product);
        } else if (key.equals(ServiceObserverKeys.PRODUCT_ORDERED)) {
            Order order = (Order) newValue;
            if (order.getRoomNumber() == room.getNumber()) {
                ordersTable.getItems().add(order);
            }
        } else if (key.equals(ServiceObserverKeys.ORDER_COMPLETED)) {
            Order order = (Order) newValue;
            if (order.getRoomNumber() == room.getNumber()) {
                updateTotal();
            }
        }
    }
}
