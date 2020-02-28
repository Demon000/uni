package controller;

import domain.Question;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import observer.Observer;
import service.Service;

public class TeacherController implements Observer {
    public static final String VIEW_NAME = "/TeacherView.fxml";
    public static final String VIEW_TITLE = "Teacher window";

    @FXML
    private TableView<Question> availableQuestionsTable;

    @FXML
    private TableColumn<Question, String> availableIdColumn;

    @FXML
    private TableColumn<Question, String> availableDescriptionColumn;

    @FXML
    private TableColumn<Question, String> availablePointsColumn;

    @FXML
    private TableView<Question> askedQuestionsTable;

    @FXML
    private TableColumn<Question, String> askedIdColumn;

    @FXML
    private TableColumn<Question, String> askedDescriptionColumn;

    @FXML
    private TableColumn<Question, String> askedPointsColumn;

    @FXML
    private TextField idField;

    @FXML
    private TextArea descriptionField;

    @FXML
    private TextField pointsField;

    private Service service;

    public TeacherController(Service service) {
        this.service = service;
    }

    private Question getSelected() {
        return availableQuestionsTable.getSelectionModel().getSelectedItem();
    }

    public void refreshTables() {
        availableQuestionsTable.getItems().setAll(service.getAvailableQuestions());
        askedQuestionsTable.getItems().setAll(service.getAskedQuestions());
    }

    @FXML
    public void initialize() {
        availableIdColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        availableDescriptionColumn.setCellValueFactory(new PropertyValueFactory<>("description"));
        availablePointsColumn.setCellValueFactory(new PropertyValueFactory<>("points"));

        askedIdColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        askedDescriptionColumn.setCellValueFactory(new PropertyValueFactory<>("description"));
        askedPointsColumn.setCellValueFactory(new PropertyValueFactory<>("points"));

        refreshTables();
    }

    @FXML
    void onAskQuestionButtonPress(ActionEvent event) {
        Question question = getSelected();
        if (question == null) {
            return;
        }

        service.askQuestion(question.getId());
        refreshTables();
    }

    @FXML
    void onEndExamButtonPress(ActionEvent event) {
        service.endExam();
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {

    }
}
