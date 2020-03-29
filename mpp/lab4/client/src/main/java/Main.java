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
    public static ClientMessageHandler messageHandler;

    public static void main(String[] args) {
        launch(args);
    }

    public void createMessageHandler() {
        try {
            messageHandler = ClientMessageHandler.createForAddress(serverAddress, serverPort);
        } catch (IOException e) {
            System.exit(-1);
        }
    }

    public void startMessageHandler() {
        messageHandler.start();
    }

    public void stopMessageHandler() {
        try {
            messageHandler.stop();
        } catch (IOException e) {
            System.exit(-1);
        }
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        createMessageHandler();
        startMessageHandler();

        LoginController windowsController = new LoginController(messageHandler);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(LoginController.VIEW_NAME));
        loader.setController(windowsController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(LoginController.VIEW_TITLE);
        primaryStage.show();
    }

    @Override
    public void stop(){
        stopMessageHandler();
    }
}
