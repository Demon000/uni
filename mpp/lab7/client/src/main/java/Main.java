import controller.ArbiterController;
import controller.IController;
import controller.LoginController;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import service.GrpcService;
import service.IService;
import service.IServiceObserver;
import utils.Configuration;

import java.io.IOException;

import static utils.FxUtils.showErrorAlert;

public class Main extends Application implements IServiceObserver {
    public static Configuration configuration = new Configuration(Main.class);
    public static String serverAddress = configuration.getValue("server_address", "127.0.0.1");
    public static Integer serverPort = configuration.getIntegerValue("server_port", 8080);
    public static IService service;

    private Stage primaryStage;
    private LoginController loginController;
    private Scene loginScene;
    private ArbiterController arbiterController;
    private Scene arbiterScene;

    public static void main(String[] args) {
        launch(args);
    }

    public void createLoginScene() {
        loginController = new LoginController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(loginController.getFXMLFilePath()));
        loader.setController(loginController);

        try {
            loginScene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void createArbiterScene() {
        arbiterController = new ArbiterController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(arbiterController.getFXMLFilePath()));
        loader.setController(arbiterController);

        try {
            arbiterScene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void showSceneOnPrimaryStage(Scene scene, IController controller) {
        if (primaryStage.getScene() == scene) {
            return;
        }

        if (primaryStage.isShowing()) {
            primaryStage.hide();
        }

        primaryStage.setScene(scene);
        primaryStage.setTitle(controller.getStageTitle());
        primaryStage.show();
        controller.onWindowShow();
    }

    public void showLoginScene() {
        if (loginScene == null) {
            createLoginScene();
        }
        showSceneOnPrimaryStage(loginScene, loginController);
    }

    public void showArbiterScene() {
        if (arbiterScene == null) {
            createArbiterScene();
        }
        showSceneOnPrimaryStage(arbiterScene, arbiterController);
    }

    public void createService() {
        service = new GrpcService(serverAddress, serverPort);
        service.addObserver(this);
    }

    public void stopLoginController() {
        if (loginController != null) {
            loginController.stop();
        }
    }

    public void stopArbiterController() {
        if (arbiterController != null) {
            arbiterController.stop();
        }
    }

    public void destroyService() {
        service.removeObserver(this);
    }

    public void stopService() {
        service.stop();
    }

    @Override
    public void start(Stage primaryStage) {
        this.primaryStage = primaryStage;

        createService();

        showLoginScene();
    }

    @Override
    public void stop() {
        stopLoginController();
        stopArbiterController();
        service.logout();
        stopService();
        destroyService();
        // printRunningThreads();
    }

    @Override
    public void onLoginStatusChange(boolean loggedIn) {
        if (loggedIn) {
            Platform.runLater(this::showArbiterScene);
        } else {
            stopService();
            Platform.runLater(() -> {
                showErrorAlert("Arbiter is no longer logged in");
                showLoginScene();
            });
        }
    }
}
