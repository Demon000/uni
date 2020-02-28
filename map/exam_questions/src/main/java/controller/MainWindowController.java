package controller;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import service.Service;

import java.io.IOException;

public class MainWindowController {
    public static final String VIEW_NAME = "/MainWindowView.fxml";
    public static final String VIEW_TITLE = "Main window";

    Service service;
    boolean teacherViewLaunched;

    public MainWindowController(Service service) {
        this.service = service;
    }

    private void launchTeacherView() {

    }

    @FXML
    void onStudentButtonAction(ActionEvent event) {
        StudentController studentController = new StudentController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(StudentController.VIEW_NAME));
        loader.setController(studentController);

        Scene scene = null;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        stage.setScene(scene);
        stage.setTitle(StudentController.VIEW_TITLE);
        stage.show();
    }

    @FXML
    void onTeacherButtonAction(ActionEvent event) {
        if (teacherViewLaunched) {
            return;
        }

        teacherViewLaunched = true;

        TeacherController teacherController = new TeacherController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(TeacherController.VIEW_NAME));
        loader.setController(teacherController);

        Scene scene = null;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        stage.setScene(scene);
        stage.setTitle(TeacherController.VIEW_TITLE);
        stage.show();
    }
}
