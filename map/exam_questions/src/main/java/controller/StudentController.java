package controller;

import domain.Question;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import observer.Observer;
import service.Service;
import service.ServiceObserverKeys;

public class StudentController implements Observer {
    public static final String VIEW_NAME = "/StudentView.fxml";
    public static final String VIEW_TITLE = "Student window";

    private Service service;
    boolean loggedIn;

    @FXML
    private TableView<Question> availableQuestionsTable;

    @FXML
    private TableColumn<Question, String> availableIdColumn;

    @FXML
    private TableColumn<Question, String> availableDescriptionColumn;

    @FXML
    private TableColumn<Question, String> availablePointsColumn;

    @FXML
    private Label questionIdField;

    @FXML
    private Label questionDescriptionField;

    @FXML
    private ToggleGroup questionChoiceToggleGroup;


    @FXML
    private RadioButton firstRadioButton;

    @FXML
    private RadioButton secondRadioButton;

    @FXML
    private RadioButton thirdRadioButton;

    @FXML
    private TextField nameField;

    @FXML
    private Button loginButton;

    @FXML
    private Button answerQuestionButton;

    public StudentController(Service service) {
        this.service = service;
    }

    public int getChoiceId() {
        RadioButton button = (RadioButton) questionChoiceToggleGroup.getSelectedToggle();
        if (button == firstRadioButton) {
            return 1;
        } else if (button == secondRadioButton) {
            return 2;
        } else if (button == thirdRadioButton) {
            return 3;
        }

        return -1;
    }

    private Question getSelected() {
        return availableQuestionsTable.getSelectionModel().getSelectedItem();
    }

    private void setFieldsData(Question question) {
        if (question == null) {
            questionIdField.setText("");
            questionDescriptionField.setText("");
            firstRadioButton.setVisible(false);
            secondRadioButton.setVisible(false);
            thirdRadioButton.setVisible(false);
            firstRadioButton.setText("");
            secondRadioButton.setText("");
            thirdRadioButton.setText("");
        } else {
            questionIdField.setText(question.getId() + ".");
            questionDescriptionField.setText(question.getDescription());
            firstRadioButton.setVisible(true);
            secondRadioButton.setVisible(true);
            thirdRadioButton.setVisible(true);
            firstRadioButton.setText(question.getFirstChoice());
            secondRadioButton.setText(question.getSecondChoice());
            thirdRadioButton.setText(question.getThirdChoice());
        }

        updateAnswerQuestionButtonDisable();
    }

    private void updateAnswerQuestionButtonDisable() {
        if (loggedIn && getSelected() != null) {
            answerQuestionButton.setDisable(false);
        } else {
            answerQuestionButton.setDisable(true);
        }
    }

    @FXML
    public void initialize() {
        availableIdColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        availableDescriptionColumn.setCellValueFactory(new PropertyValueFactory<>("description"));
        availablePointsColumn.setCellValueFactory(new PropertyValueFactory<>("points"));

        answerQuestionButton.setDisable(true);

        availableQuestionsTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            setFieldsData(newSelection);
        });

        setFieldsData(null);
        service.addObserver(this);
    }

    @FXML
    void onAnswerQuestionPress(ActionEvent event) {
        Question question = getSelected();
        if (question == null) {
            return;
        }

        int choiceId = getChoiceId();
        if (choiceId < 1) {
            return;
        }

        String name = nameField.getText();
        service.answerQuestion(name, question.getId(), choiceId);
        availableQuestionsTable.getItems().remove(question);
    }

    @FXML
    void onLoginButtonPress(ActionEvent event) {
        String name = nameField.getText();
        if (service.isStudentLoggedIn(name)) {
            return;
        }

        service.logStudentIn(name);
        loggedIn = true;
        nameField.setDisable(true);
        loginButton.setDisable(true);
        updateAnswerQuestionButtonDisable();
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        if (key.equals(ServiceObserverKeys.QUESTION_ASKED)) {
            Question question = (Question) newValue;
            availableQuestionsTable.getItems().add(question);
        }
    }
}
