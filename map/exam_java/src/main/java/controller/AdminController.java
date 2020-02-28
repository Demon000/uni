package controller;

import domain.Order;
import domain.Product;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import observer.Observer;
import service.Service;
import service.ServiceObserverKeys;

import java.time.LocalDateTime;
import java.util.List;

public class AdminController implements Observer {
    public static final String VIEW_NAME = "/AdminView.fxml";
    public static final String VIEW_TITLE = "Admin window";

    private final Service service;

    @FXML
    private TableView<Product> productsTable;

    @FXML
    private TableColumn<Product, String> productNameColumn;

    @FXML
    private TableColumn<Product, Float> productPriceColumn;

    @FXML
    private TextField productNameField;

    @FXML
    private TextField productPriceField;

    @FXML
    private TableView<Order> pendingOrdersTable;

    @FXML
    private TableColumn<Order, Integer> orderRoomNumberColumn;

    @FXML
    private TableColumn<Order, String> orderProductNameColumn;

    @FXML
    private TableColumn<Order, Float> orderProductPriceColumn;

    @FXML
    private TableColumn<Order, LocalDateTime> orderTimeColumn;

    public AdminController(Service service) {
        this.service = service;
    }

    @FXML
    public void initialize() {
        productNameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        productPriceColumn.setCellValueFactory(new PropertyValueFactory<>("price"));
        loadProductsTable();

        orderRoomNumberColumn.setCellValueFactory(new PropertyValueFactory<>("roomNumber"));
        orderProductNameColumn.setCellValueFactory(new PropertyValueFactory<>("productName"));
        orderProductPriceColumn.setCellValueFactory(new PropertyValueFactory<>("productPrice"));
        orderTimeColumn.setCellValueFactory(new PropertyValueFactory<>("time"));

        service.addObserver(this);
    }

    private List<Order> getSelectedOrders() {
        return pendingOrdersTable.getSelectionModel().getSelectedItems();
    }

    private void loadProductsTable() {
        productsTable.getItems().setAll(service.getProducts());
    }

    @FXML
    void onAddProductButtonPress(ActionEvent event) {
        String productName = productNameField.getText();
        String productPriceString = productPriceField.getText();
        float productPrice;

        if (productName.isEmpty()) {
            return;
        }

        if (productPriceString.isEmpty()) {
            return;
        }


        try {
            productPrice = Float.parseFloat(productPriceString);
        } catch (NumberFormatException e) {
            return;
        }

        service.addProduct(productName, productPrice);
    }

    @FXML
    void onCompleteOrderButtonPress(ActionEvent event) {
        getSelectedOrders().forEach(service::completeOrder);
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        if (key.equals(ServiceObserverKeys.PRODUCT_ADDED)) {
            Product product = (Product) newValue;
            productsTable.getItems().add(product);
        } else if (key.equals(ServiceObserverKeys.PRODUCT_ORDERED)) {
            Order order = (Order) newValue;
            pendingOrdersTable.getItems().add(order);
        } else if (key.equals(ServiceObserverKeys.ORDER_COMPLETED)) {
            Order order = (Order) newValue;
            pendingOrdersTable.getItems().remove(order);
        }
    }
}
