import controller.AdminController;
import controller.RoomController;
import domain.Order;
import domain.OrderStringSerializer;
import domain.Product;
import domain.Room;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repository.BaseRepository;
import repository.IRepository;
import repository.StringFileRepository;
import service.Service;

import java.io.IOException;

public class Main extends Application {
    public static String[] arguments;

    public static void main(String[] args) {
        arguments = new String[] {"401", "402", "403"};
        launch(args);
    }

    public Stage createRoomWindow(Service service, Room room) {
        RoomController roomController = new RoomController(service, room);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(RoomController.VIEW_NAME));
        loader.setController(roomController);

        Scene scene = null;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }

        stage.setScene(scene);
        return stage;
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        IRepository<Integer, Room> roomsRepository = new BaseRepository<>();
        IRepository<String, Product> productsRepository = new BaseRepository<>();
        IRepository<Integer, Order> pendingOrdersRepository = new BaseRepository<>();

        for (String argument : arguments) {
            int roomNumber = Integer.parseInt(argument);
            Room room = new Room(roomNumber);
            roomsRepository.add(room);
        }

        productsRepository.add(new Product("Mar", 10));
        productsRepository.add(new Product("Banana", 10));
        productsRepository.add(new Product("Sampanie", 100));

        OrderStringSerializer orderStringSerializer = new OrderStringSerializer();
        IRepository<Integer, Order> completedOrdersRepository = new StringFileRepository<>("Comenzi.txt",
                orderStringSerializer);
        completedOrdersRepository.empty();

        Service service = new Service(roomsRepository, productsRepository,
                pendingOrdersRepository, completedOrdersRepository);

        AdminController mainWindowController = new AdminController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(AdminController.VIEW_NAME));
        System.out.println(loader.getLocation());

        loader.setController(mainWindowController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(AdminController.VIEW_TITLE);
        primaryStage.show();

        for (Room room : roomsRepository.find()) {
            Stage secondaryStage = createRoomWindow(service, room);
            secondaryStage.setTitle(String.format(RoomController.VIEW_TITLE_FORMAT, room.getNumber()));
            secondaryStage.show();
        }
    }
}
