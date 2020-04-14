package controller;

import domain.Arbiter;
import domain.Score;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import service.IService;
import utils.ServiceError;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static utils.FxUtils.showErrorAlert;

public class LoginController {
    public static final String VIEW_NAME = "/LoginView.fxml";
    public static final String VIEW_TITLE = "Login";

    ExecutorService executor = Executors.newFixedThreadPool(10);
    private final IService service;

    @FXML
    private TextField nameField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;

    public LoginController(IService service) {
        this.service = service;
    }

    @FXML
    public void initialize() {
        passwordField.setOnKeyPressed(this::onPasswordFieldKeyPressed);
    }

    public void stop() {
        executor.shutdownNow();
    }

    private void closeLoginWindow() {
        Stage loginWindow = (Stage) loginButton.getScene().getWindow();
        loginWindow.close();
    }

    private void loginArbiter() {
        executor.execute(() -> {
            try {
                Arbiter arbiter = service.loginArbiter(nameField.getText(), passwordField.getText());
                Platform.runLater(() -> openArbiterWindow(arbiter));
            } catch (ServiceError e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
    }

    private void openArbiterWindow(Arbiter arbiter) {
        ArbiterController arbiterController = new ArbiterController(service, arbiter);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(ArbiterController.VIEW_NAME));
        loader.setController(arbiterController);

        Scene scene;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            showErrorAlert(e.getMessage());
            return;
        }

        stage.setScene(scene);
        stage.setTitle(ArbiterController.VIEW_TITLE);
        stage.show();
        stage.setOnCloseRequest((event) -> arbiterController.stop());

        closeLoginWindow();
    }

    private void onPasswordFieldKeyPressed(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            loginArbiter();
        }
    }

    @FXML
    void onLoginButtonAction(ActionEvent event) {
        loginArbiter();
    }
}
