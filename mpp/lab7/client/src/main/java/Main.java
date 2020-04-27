import controller.LoginController;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import org.mindrot.jbcrypt.BCrypt;
import service.GrpcService;
import service.IService;
import utils.Configuration;

import java.io.IOException;

import static utils.ThreadUtils.printRunningThreads;

public class Main extends Application {
    public static Configuration configuration = new Configuration(Main.class);
    public static String serverAddress = configuration.getValue("server_address", "127.0.0.1");
    public static Integer serverPort = configuration.getIntegerValue("server_port", 8080);
    public static IService service;

    public static void main(String[] args) {
        launch(args);
    }

    public void createService() {
        service = new GrpcService(serverAddress, serverPort);
    }

    public void stopService() {
        service.stop();
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        createService();

        String hashed = BCrypt.hashpw("haha", BCrypt.gensalt());
        System.out.println(hashed);

        LoginController loginController = new LoginController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(LoginController.VIEW_NAME));
        loader.setController(loginController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(LoginController.VIEW_TITLE);
        primaryStage.setOnHidden((WindowEvent e) -> loginController.stop());
        primaryStage.show();

//        printRunningThreads();
    }

    @Override
    public void stop() {
        stopService();
    }
}
