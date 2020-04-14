import controller.LoginController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import service.ClientMessageService;
import service.IService;
import utils.Configuration;

import java.io.IOException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Main extends Application {
    public static Configuration configuration = new Configuration(Main.class);
    public static String serverAddress = configuration.getValue("server_address", "127.0.0.1");
    public static Integer serverPort = configuration.getIntegerValue("server_port", 8080);
    public static IService service;

    public static void main(String[] args) {
        launch(args);
    }

    public void createService() {
//        service = new ClientMessageService(serverAddress, serverPort);
        try {
            service = (IService) LocateRegistry.getRegistry(serverAddress, serverPort).lookup(IService.class.getSimpleName());
        } catch (NotBoundException | RemoteException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public void stopService() {
//        try {
//            service.stop();
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        createService();

        LoginController loginController = new LoginController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(LoginController.VIEW_NAME));
        loader.setController(loginController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(LoginController.VIEW_TITLE);
        primaryStage.show();
        primaryStage.setOnCloseRequest(event -> loginController.stop());
    }

    @Override
    public void stop(){
        stopService();
    }
}
