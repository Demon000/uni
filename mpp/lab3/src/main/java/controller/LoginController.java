package controller;

import domain.Arbiter;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import repository.RepositoryError;
import service.Service;

import java.io.IOException;

import static utils.FxUtils.showErrorAlert;

public class LoginController {
    public static final String VIEW_NAME = "/LoginView.fxml";
    public static final String VIEW_TITLE = "Login";

    private final Service service;

    public LoginController(Service service) {
        this.service = service;
    }

    @FXML
    private TextField nameField;

    @FXML
    private PasswordField passwordField;

    @FXML
    private Button loginButton;

    private void closeLoginWindow() {
        Stage loginWindow = (Stage) loginButton.getScene().getWindow();
        loginWindow.close();
    }

    private void openArbiterWindow() {
        Arbiter arbiter;
        try {
            arbiter = service.loginArbiter(nameField.getText(), passwordField.getText());
        } catch (RepositoryError e) {
            showErrorAlert("Failed to login");
            return;
        }

        ArbiterController assignmentsController = new ArbiterController(service, arbiter);
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

    @FXML
    public void initialize() {
        passwordField.setOnKeyPressed(this::onPasswordFieldKeyPressed);
    }

    private void onPasswordFieldKeyPressed(KeyEvent keyEvent) {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            openArbiterWindow();
        }
    }

    @FXML
    void onLoginButtonAction(ActionEvent event) {
        openArbiterWindow();
    }
}
