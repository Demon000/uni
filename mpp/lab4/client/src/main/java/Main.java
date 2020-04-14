import controller.LoginController;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import service.ClientMessageService;
import utils.Configuration;

import java.io.IOException;

public class Main extends Application {
    public static Configuration configuration = new Configuration(Main.class);
    public static String serverAddress = configuration.getValue("server_address", "127.0.0.1");
    public static Integer serverPort = configuration.getIntegerValue("server_port", 8080);
    public static ClientMessageService service;

    public static void main(String[] args) {
        launch(args);
    }

    public void createService() {
        service = new ClientMessageService(serverAddress, serverPort);
    }

    public void stopService() {
        try {
            service.stop();
        } catch (IOException e) {
            e.printStackTrace();
        }
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
