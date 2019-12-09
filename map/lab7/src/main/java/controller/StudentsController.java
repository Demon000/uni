package controller;

import domain.Student;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.scene.control.*;
import javafx.scene.input.MouseEvent;
import service.CommonService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.cell.PropertyValueFactory;
import service.CommonServiceException;
import validator.ValidationException;

import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.List;

import static utils.CollectionUtils.listFromIterable;

public class StudentsController implements PropertyChangeListener {
    public static final String VIEW_NAME = "/StudentsView.fxml";
    public static final String VIEW_TITLE = "Students";

    private final CommonService service;

    @FXML
    private TableView<Student> table;

    @FXML
    private TableColumn<Student, String> firstNameColumn;

    @FXML
    private TableColumn<Student, String> lastNameColumn;

    @FXML
    private TableColumn<Student, String> emailColumn;

    @FXML
    private TableColumn<Student, String> groupColumn;

    @FXML
    private TableColumn<Student, String> professorNameColumn;

    @FXML
    private TableColumn<Student, String> motivatedWeeksColumn;

    @FXML
    private TextField firstNameField;

    @FXML
    private TextField lastNameField;

    @FXML
    private TextField emailField;

    @FXML
    private TextField groupField;

    @FXML
    private TextField professorNameField;

    @FXML
    private TextField motivatedWeeksField;

    @FXML
    private Button addButton;

    @FXML
    private Button deleteButton;

    @FXML
    private Button updateButton;

    public StudentsController(CommonService service) {
        this.service = service;
    }

    @FXML
    public void initialize() {
        loadTableData();

        firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        groupColumn.setCellValueFactory(new PropertyValueFactory<>("group"));
        professorNameColumn.setCellValueFactory(new PropertyValueFactory<>("professorName"));
        motivatedWeeksColumn.setCellValueFactory(studentCellDataFeatures -> {
            Student student = studentCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(student.getMotivatedWeeksString());
        });

        table.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection == null) {
                emptyFieldsData();
                setButtonsDisable(true);
            } else {
                setFieldsData(newSelection);
                setButtonsDisable(false);
            }
        });

        table.setRowFactory(tableView2 -> {
            final TableRow<Student> row = new TableRow<>();

            row.addEventFilter(MouseEvent.MOUSE_PRESSED, event -> {
                final int index = row.getIndex();
                if (index >= 0 && index < table.getItems().size() && table.getSelectionModel().isSelected(index)  ) {
                    table.getSelectionModel().clearSelection();
                    event.consume();
                }
            });

            return row;
        });

        setButtonsDisable(true);
    }

    private void setButtonsDisable(boolean disabled) {
        updateButton.setDisable(disabled);
        deleteButton.setDisable(disabled);
    }

    public void showError(String message) {
        Alert alert = new Alert(Alert.AlertType.ERROR, message, ButtonType.OK);
        alert.showAndWait();
    }

    private void setTableData(List<Student> students) {
        table.getItems().setAll(students);
    }

    private void loadTableData() {
        Iterable<Student> students = service.getStudents();
        setTableData(listFromIterable(students));
    }

    private void setFieldsData(String firstName, String lastName, String email, String group,
                               String professorName, String motivatedWeeksString) {
        firstNameField.setText(firstName);
        lastNameField.setText(lastName);
        emailField.setText(email);
        groupField.setText(group);
        professorNameField.setText(professorName);
        motivatedWeeksField.setText(motivatedWeeksString);
    }

    private void emptyFieldsData() {
        setFieldsData("", "", "", "", "", "");
    }

    private void setFieldsData(Student student) {
        setFieldsData(student.getFirstName(), student.getLastName(), student.getEmail(), student.getGroup(),
                student.getProfessorName(), student.getMotivatedWeeksString());
    }

    private Student getSelectedStudent() {
        return table.getSelectionModel().getSelectedItem();
    }

    @FXML
    void onFilterFieldAction(ActionEvent event) {

    }

    @FXML
    void onAddButtonAction(ActionEvent event) {

    }

    @FXML
    void onDeleteButtonAction(ActionEvent event) {
        Student student = getSelectedStudent();
        if (student == null) {
            showError("No student selected!");
            return;
        }

        try {
            service.deleteStudent(student.getId());
        } catch (CommonServiceException e) {
            showError(e.getMessage());
        }
    }

    @FXML
    void onUpdateButtonAction(ActionEvent event) {
        Student student = getSelectedStudent();
        if (student == null) {
            showError("No student selected!");
            return;
        }

        try {
            service.updateStudent(student.getId(), firstNameField.getText(), lastNameField.getText(),
                    emailField.getText(), groupField.getText(),
                    professorNameField.getText(),
                    Student.stringToMotivatedWeeks(motivatedWeeksField.getText()));
        } catch (CommonServiceException | ValidationException e) {
            showError(e.getMessage());
        }
    }

    @Override
    public void propertyChange(PropertyChangeEvent propertyChangeEvent) {
        System.out.println("fire");
        System.out.println(propertyChangeEvent.getPropertyName());
        switch (propertyChangeEvent.getPropertyName()) {
            case "students":
                System.out.println("fire again");
                loadTableData();
                break;
            default:
                break;
        }
    }
}
