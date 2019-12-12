package controller;

import domain.Student;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.scene.control.*;
import service.CommonService;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.cell.PropertyValueFactory;
import service.CommonServiceException;
import utils.FilteredTableWrapper;
import observer.Observer;
import validator.ValidationException;

import static utils.CollectionUtils.listFromIterable;
import static utils.FxUtils.*;

public class StudentsController implements Observer {
    public static final String VIEW_NAME = "/StudentsView.fxml";
    public static final String VIEW_TITLE = "Students";

    private final CommonService service;
    private FilteredTableWrapper<Student> ftw;

    @FXML
    private TableView<Student> table;

    @FXML
    private TableColumn<Student, String> idColumn;

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
    private TextField filterField;

    @FXML
    private TextField idField;

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
        ftw = new FilteredTableWrapper<>(table, filterField);

        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        groupColumn.setCellValueFactory(new PropertyValueFactory<>("group"));
        professorNameColumn.setCellValueFactory(new PropertyValueFactory<>("professorName"));
        motivatedWeeksColumn.setCellValueFactory(studentCellDataFeatures -> {
            Student student = studentCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(student.getMotivatedWeeksString());
        });

        addTableDeselect(table);
        addFieldNumber(idField);
        setFieldsData();

        table.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            if (newSelection == null) {
                setFieldsData();
                setButtonsDisable(true);
            } else {
                setFieldsData(newSelection);
                setButtonsDisable(false);
            }
        });

        setButtonsDisable(true);

        service.addObserver(this);

        loadTableData();
    }

    private void loadTableData() {
        Iterable<Student> elements = service.getStudents();
        ftw.setTableData(listFromIterable(elements));
    }

    private void setButtonsDisable(boolean disabled) {
        updateButton.setDisable(disabled);
        deleteButton.setDisable(disabled);
    }

    private void setFieldsData(String id, String firstName, String lastName, String email, String group,
                               String professorName, String motivatedWeeksString) {
        idField.setText(id);
        firstNameField.setText(firstName);
        lastNameField.setText(lastName);
        emailField.setText(email);
        groupField.setText(group);
        professorNameField.setText(professorName);
        motivatedWeeksField.setText(motivatedWeeksString);
    }

    private void setFieldsData() {
        setFieldsData("", "", "", "","",
                "", "");
    }

    private void setFieldsData(Student student) {
        setFieldsData(student.getId(), student.getFirstName(), student.getLastName(),
                student.getEmail(), student.getGroup(), student.getProfessorName(),
                student.getMotivatedWeeksString());
    }

    @FXML
    void onFilterFieldAction(ActionEvent event) {
        loadTableData();
    }

    @FXML
    void onAddButtonAction(ActionEvent event) {
        try {
            Student student = service.addStudent(idField.getText(), firstNameField.getText(), lastNameField.getText(),
                    emailField.getText(), groupField.getText(),
                    professorNameField.getText(),
                    Student.stringToMotivatedWeeks(motivatedWeeksField.getText()));
            ftw.setSelected(student);
        } catch (CommonServiceException | ValidationException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @FXML
    void onDeleteButtonAction(ActionEvent event) {
        Student student = ftw.getSelected();
        if (student == null) {
            showErrorAlert("No student selected!");
            return;
        }

        try {
            service.deleteStudent(student.getId());
        } catch (CommonServiceException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @FXML
    void onUpdateButtonAction(ActionEvent event) {
        Student student = ftw.getSelected();
        if (student == null) {
            showErrorAlert("No student selected!");
            return;
        }

        try {
            service.updateStudent(student.getId(), firstNameField.getText(), lastNameField.getText(),
                    emailField.getText(), groupField.getText(),
                    professorNameField.getText(),
                    Student.stringToMotivatedWeeks(motivatedWeeksField.getText()));
        } catch (CommonServiceException | ValidationException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        if ("students".equals(key)) {
            loadTableData();
        }
    }
}
