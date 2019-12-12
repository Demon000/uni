package controller;

import domain.Assignment;
import domain.Grade;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import service.CommonService;
import time.UniversityYear;

import java.io.IOException;

public class WindowsController {
    public static final String VIEW_NAME = "/WindowsView.fxml";
    public static final String VIEW_TITLE = "Windows";

    private final CommonService service;
    private final UniversityYear year;

    public WindowsController(CommonService service, UniversityYear year) {
        this.service = service;
        this.year = year;
    }

    @FXML
    void onStudentsButtonAction(ActionEvent event) {
        StudentsController studentsController = new StudentsController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(StudentsController.VIEW_NAME));
        loader.setController(studentsController);

        Scene scene = null;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        stage.setScene(scene);
        stage.setTitle(StudentsController.VIEW_TITLE);
        stage.show();
    }

    @FXML
    void onAssignmentsButtonAction(ActionEvent event) {
        AssignmentsController assignmentsController = new AssignmentsController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(AssignmentsController.VIEW_NAME));
        loader.setController(assignmentsController);

        Scene scene = null;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        stage.setScene(scene);
        stage.setTitle(AssignmentsController.VIEW_TITLE);
        stage.show();
    }

    @FXML
    void onGradesButtonAction(ActionEvent event) {
        GradesController assignmentsController = new GradesController(service, year);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(GradesController.VIEW_NAME));
        loader.setController(assignmentsController);

        Scene scene = null;
        Stage stage = new Stage();
        try {
            scene = new Scene(loader.load());
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        stage.setScene(scene);
        stage.setTitle(GradesController.VIEW_TITLE);
        stage.show();
    }
}
