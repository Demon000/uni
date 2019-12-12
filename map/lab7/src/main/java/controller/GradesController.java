package controller;

import domain.Assignment;
import domain.Grade;
import domain.Student;
import javafx.beans.property.ReadOnlyBooleanProperty;
import javafx.beans.property.ReadOnlyBooleanWrapper;
import javafx.beans.property.ReadOnlyDoubleWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.CheckBoxTableCell;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.util.converter.LocalDateStringConverter;
import observer.Observer;
import service.CommonService;
import service.CommonServiceException;
import time.UniversityYear;
import time.UniversityYearError;
import utils.FilteredTableWrapper;
import validator.ValidationException;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

import static utils.CollectionUtils.listFromIterable;
import static utils.FxUtils.*;

public class GradesController implements Observer {
    public static final String VIEW_NAME = "/GradesView.fxml";
    public static final String VIEW_TITLE = "Grades";

    private final CommonService service;
    private UniversityYear year;
    private FilteredTableWrapper<Student> studentFtw;
    private FilteredTableWrapper<Assignment> assignmentFtw;

    @FXML
    private TableView<Student> studentTable;

    @FXML
    private TableColumn<Student, String> studentFirstNameColumn;

    @FXML
    private TableColumn<Student, String> studentLastNameColumn;

    @FXML
    private TableColumn<Student, String> studentGroupColumn;

    @FXML
    private TableColumn<Student, String> studentMotivatedWeeksColumn;

    @FXML
    private TableColumn<Student, String> studentAverageGradeColumn;

    @FXML
    private TableColumn<Student, Boolean> studentPassingGradeColumn;

    @FXML
    private TableColumn<Student, Boolean> studentAllOnTimeColumn;

    @FXML
    private TextField studentFilterField;

    @FXML
    private TableView<Assignment> assignmentTable;

    @FXML
    private TableColumn<Assignment, String> assignmentDescription;

    @FXML
    private TableColumn<Assignment, String> assignmentStartWeekColumn;

    @FXML
    private TableColumn<Assignment, String> assignmentDeadlineWeekColumn;

    @FXML
    private TextField assignmentFilterField;

    @FXML
    private DatePicker dateField;

    @FXML
    private Label weekField;

    @FXML
    private TextField valueField;

    @FXML
    private Label penaltyField;

    @FXML
    private TextField professorNameField;

    @FXML
    private TextArea feedbackField;

    @FXML
    private Button setButton;

    @FXML
    private Button deleteButton;

    public GradesController(CommonService service, UniversityYear year) {
        this.service = service;
        this.year = year;
    }

    @FXML
    public void initialize() {
        studentFtw = new FilteredTableWrapper<>(studentTable, studentFilterField);
        assignmentFtw = new FilteredTableWrapper<>(assignmentTable, assignmentFilterField);

        studentFirstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        studentLastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        studentGroupColumn.setCellValueFactory(new PropertyValueFactory<>("group"));
        studentMotivatedWeeksColumn.setCellValueFactory(studentCellDataFeatures -> {
            Student student = studentCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(student.getMotivatedWeeksString());
        });
        studentAverageGradeColumn.setCellValueFactory(studentCellDataFeatures -> {
            Student student = studentCellDataFeatures.getValue();
            double averageGrade = service.getStudentAverageGrade(student.getId());
            return new ReadOnlyStringWrapper(String.valueOf(averageGrade));
        });
        studentPassingGradeColumn.setCellFactory( tc -> new CheckBoxTableCell<>());
        studentPassingGradeColumn.setCellValueFactory(studentCellDataFeatures -> {
            Student student = studentCellDataFeatures.getValue();
            double averageGrade = service.getStudentAverageGrade(student.getId());
            return new ReadOnlyBooleanWrapper(averageGrade >= 4.0);
        });
        studentAllOnTimeColumn.setCellFactory( tc -> new CheckBoxTableCell<>());
        studentAllOnTimeColumn.setCellValueFactory(studentCellDataFeatures -> {
            Student student = studentCellDataFeatures.getValue();
            double averageGrade = service.getStudentAverageGrade(student.getId());
            return new ReadOnlyBooleanWrapper(averageGrade == 10.0);
        });

        assignmentDescription.setCellValueFactory(new PropertyValueFactory<>("description"));
        assignmentStartWeekColumn.setCellValueFactory(new PropertyValueFactory<>("startWeek"));
        assignmentDeadlineWeekColumn.setCellValueFactory(new PropertyValueFactory<>("deadlineWeek"));

        dateField.setConverter(new LocalDateStringConverter(Grade.DATE_FORMATTER, Grade.DATE_FORMATTER));

        addTableDeselect(studentTable);
        addTableDeselect(assignmentTable);
        addFieldNumber(valueField);
        setFieldsData();
        setDateFieldData();
        setPenaltyFieldData();

        studentTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            onSelectionChanged(studentFtw.getSelected(), assignmentFtw.getSelected());
        });

        assignmentTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            onSelectionChanged(studentFtw.getSelected(), assignmentFtw.getSelected());
        });

        setButtonsDisable(true);

        service.addObserver(this);

        loadStudentTableData();
        loadAssignmentTableData();
    }

    private void loadStudentTableData() {
        Iterable<Student> elements = service.getStudents();
        studentFtw.setTableData(listFromIterable(elements));
    }

    private void loadAssignmentTableData() {
        Iterable<Assignment> elements = service.getAssignments();
        assignmentFtw.setTableData(listFromIterable(elements));
    }

    private void setButtonsDisable(boolean disabled) {
        setButton.setDisable(disabled);
        deleteButton.setDisable(disabled);
    }

    private void setFieldsData(String valueString, String professorName, String feedback) {
        valueField.setText(valueString);
        professorNameField.setText(professorName);
        feedbackField.setText(feedback);
    }

    private void setFieldsData() {
        setFieldsData("", "", "");
    }

    private void setWeekFieldData(LocalDate date) {
        try {
            weekField.setText(String.format("Week: %d", year.getWeeksSinceStart(date)));
        } catch (UniversityYearError e) {
            weekField.setText(e.getMessage());
        }
    }

    private void setDateFieldData(LocalDate date) {
        dateField.setValue(date);
        setWeekFieldData(date);
    }

    private void setDateFieldData() {
        setDateFieldData(LocalDate.now());
    }

    private void setPenaltyFieldData(long penalty) {
        String penaltyString;
        if (penalty == 0) {
            penaltyString = "";
        } else {
            penaltyString = String.format("A penalty of %d points will be applied to the grade.", penalty);
        }

        penaltyField.setText(penaltyString);
    }

    private void setPenaltyFieldData(Student student, Assignment assignment, LocalDate date) {
        long penalty;
        try {
            penalty = service.getGradePenalty(student.getId(), assignment.getId(), date);
        } catch (CommonServiceException | UniversityYearError e) {
            penalty = 0;
        }

        setPenaltyFieldData(penalty);
    }

    private void setPenaltyFieldData(Grade grade) {
        setPenaltyFieldData(grade.getPenalty());
    }

    private void setPenaltyFieldData() {
        setPenaltyFieldData(0);
    }

    private void setFieldsData(Student student, Assignment assignment) {
        Grade grade;
        try {
            grade = service.getGradeById(student.getId(), assignment.getId());
        } catch (CommonServiceException e) {
            setFieldsData();
            // Student and assignment are not null, we can predict the penalty
            setPenaltyFieldData(student, assignment, dateField.getValue());
            return;
        }

        setFieldsData(grade.getValueString(), grade.getProfessorName(), grade.getFeedback());
        setDateFieldData(grade.getDate());
        // Grade is not null, set the penalty to its value
        setPenaltyFieldData(grade);
    }

    void onSelectionChanged(Student student, Assignment assignment) {
        if (student == null || assignment == null) {
            setFieldsData();
            // Student or assignment is null, we cannot predict the penalty
            setPenaltyFieldData();
            setButtonsDisable(true);
            return;
        }

        setFieldsData(student, assignment);
        setButtonsDisable(false);
    }

    @FXML
    void onStudentFilterFieldAction(ActionEvent event) {
        loadStudentTableData();
    }

    @FXML
    void onAssignmentFilterFieldAction(ActionEvent event) {
        loadAssignmentTableData();
    }

    @FXML
    void onDateFieldAction(ActionEvent event) {
        Student student = studentFtw.getSelected();
        Assignment assignment = assignmentFtw.getSelected();

        setWeekFieldData(dateField.getValue());

        if (student == null || assignment == null) {
            // Student or assignment is null, we cannot predict the penalty
            return;
        }

        // Student and assignment are not null, we can predict the penalty
        setPenaltyFieldData(student, assignment, dateField.getValue());
    }

    @FXML
    void onSetButtonAction(ActionEvent event) {
        Student student = studentFtw.getSelected();
        Assignment assignment = assignmentFtw.getSelected();

        if (student == null) {
            showErrorAlert("No student selected");
            return;
        }

        if (assignment == null) {
            showErrorAlert("No assignment selected");
            return;
        }

        if (valueField.getText().isEmpty()) {
            showErrorAlert("Value field cannot be empty");
            return;
        }

        StringBuilder sb = new StringBuilder();
        sb.append("Assignment: ");
        sb.append(assignment.getDescription());
        sb.append("\n");

        sb.append("Student: ");
        sb.append(student.getFullName());
        sb.append("\n");

        try {
            sb.append("Penalty: ");
            sb.append(service.getGradePenalty(student.getId(), assignment.getId(), dateField.getValue()));
            sb.append("\n");
        } catch (CommonServiceException | UniversityYearError e) {
            showErrorAlert(e.getMessage());
            return;
        }

        sb.append("Grade: ");
        sb.append(valueField.getText());
        sb.append("\n");

        try {
            sb.append("Motivated weeks: ");
            List<Long> usedMotivatedWeeks = service.getGradeMotivatedWeeks(student.getId(), assignment.getId(), dateField.getValue());
            sb.append(Student.getMotivatedWeeksString(usedMotivatedWeeks));
            sb.append("\n");
        } catch (CommonServiceException | UniversityYearError e) {
            showErrorAlert(e.getMessage());
            return;
        }

        Alert alert = createConfirmationAlert(sb.toString());
        Optional<ButtonType> result = alert.showAndWait();
        if (result.isPresent() && result.get() == ButtonType.OK){
            try {
                service.setGrade(student.getId(), assignment.getId(), dateField.getValue(),
                        Integer.parseInt(valueField.getText()), professorNameField.getText(),
                        feedbackField.getText());
            } catch (CommonServiceException | ValidationException | UniversityYearError e) {
                showErrorAlert(e.getMessage());
            }
        }
    }

    @FXML
    void onDeleteButtonAction(ActionEvent event) {
        Student student = studentFtw.getSelected();
        Assignment assignment = assignmentFtw.getSelected();

        if (student == null) {
            showErrorAlert("No student selected");
            return;
        }

        if (assignment == null) {
            showErrorAlert("No assignment selected");
            return;
        }

        try {
            service.deleteGrade(student.getId(), assignment.getId());
            setFieldsData();
        } catch (CommonServiceException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        if ("students".equals(key)) {
            loadStudentTableData();
        } else if ("assignments".equals(key)) {
            loadAssignmentTableData();
        } else if ("grades".equals(key)) {
            loadStudentTableData();
        }
    }
}
