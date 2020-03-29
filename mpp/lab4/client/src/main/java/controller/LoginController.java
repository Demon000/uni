package controller;

import domain.Arbiter;
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
import message.*;

import java.io.IOException;

import static utils.FxUtils.showErrorAlert;

public class LoginController implements ClientMessageReceiver {
    public static final String VIEW_NAME = "/LoginView.fxml";
    public static final String VIEW_TITLE = "Login";

    private final ClientMessageHandler messageHandler;

    @FXML
    private TextField nameField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;

    public LoginController(ClientMessageHandler messageHandler) {
        this.messageHandler = messageHandler;
    }

    @FXML
    public void initialize() {
        passwordField.setOnKeyPressed(this::onPasswordFieldKeyPressed);
        messageHandler.addReceiver(this);
    }

    private void closeLoginWindow() {
        Stage loginWindow = (Stage) loginButton.getScene().getWindow();
        loginWindow.close();
        messageHandler.removeReceiver(this);
    }

    private void requestArbiterLogin() {
        messageHandler.requestLogin(new LoginData(nameField.getText(), passwordField.getText()));
    }

    private void openArbiterWindow(Arbiter arbiter) {
        ArbiterController assignmentsController = new ArbiterController(messageHandler, arbiter);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(ArbiterController.VIEW_NAME));
        loader.setController(assignmentsController);

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

        closeLoginWindow();
    }

    private void onPasswordFieldKeyPressed(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            requestArbiterLogin();
        }
    }

    @FXML
    void onLoginButtonAction(ActionEvent event) {
        requestArbiterLogin();
    }

    @Override
    public void onLoginRequestError(String error) {
        Platform.runLater(() -> showErrorAlert(error));
    }

    @Override
    public void onLoginResponse(Arbiter arbiter) {
        Platform.runLater(() -> openArbiterWindow(arbiter));
    }
}
