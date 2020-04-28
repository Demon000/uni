package controller;

import domain.Arbiter;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import service.IService;
import service.ServiceError;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static utils.FxUtils.showErrorAlert;

public class LoginController implements IController {
    @Override
    public String getStageTitle() {
        return "Login";
    }

    @Override
    public String getFXMLFilePath() {
        return "/LoginView.fxml";
    }

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
        executor.shutdown();
    }

    private void loginArbiter() {
        executor.execute(() -> {
            try {
                service.start();
                service.loginArbiter(nameField.getText(), passwordField.getText());
            } catch (ServiceError e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
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
