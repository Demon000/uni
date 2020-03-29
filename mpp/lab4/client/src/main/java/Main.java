import controller.LoginController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import message.ClientMessageHandler;
import utils.Configuration;

import java.io.IOException;

public class Main extends Application {
    public static Configuration configuration = new Configuration(Main.class);
    public static String serverAddress = configuration.getValue("server_address", "127.0.0.1");
    public static Integer serverPort = configuration.getIntegerValue("server_port", 8080);

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        ClientMessageHandler messageHandler = ClientMessageHandler.createForAddress(serverAddress, serverPort);
        messageHandler.start();

        LoginController windowsController = new LoginController(messageHandler);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(LoginController.VIEW_NAME));
        loader.setController(windowsController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(LoginController.VIEW_TITLE);
        primaryStage.show();
    }
}
