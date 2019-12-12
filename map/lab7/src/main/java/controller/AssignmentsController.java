package controller;

import domain.Assignment;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import observer.Observer;
import service.CommonService;
import service.CommonServiceException;
import utils.FilteredTableWrapper;
import validator.ValidationException;

import static utils.CollectionUtils.listFromIterable;
import static utils.FxUtils.*;

public class AssignmentsController implements Observer {
    public static final String VIEW_NAME = "/AssignmentsView.fxml";
    public static final String VIEW_TITLE = "Assignments";

    private final CommonService service;
    private FilteredTableWrapper<Assignment> ftw;


    @FXML
    private TableView<Assignment> table;

    @FXML
    private TableColumn<Assignment, String> idColumn;

    @FXML
    private TableColumn<Assignment, String> descriptionColumn;

    @FXML
    private TableColumn<Assignment, String> startWeekColumn;

    @FXML
    private TableColumn<Assignment, String> deadlineWeekColumn;

    @FXML
    private TextField filterField;

    @FXML
    private TextField idField;

    @FXML
    private TextArea descriptionField;

    @FXML
    private TextField startWeekField;

    @FXML
    private TextField deadlineWeekField;

    @FXML
    private Button addButton;

    @FXML
    private Button deleteButton;

    @FXML
    private Button updateButton;

    public AssignmentsController(CommonService service) {
        this.service = service;
    }

    @FXML
    public void initialize() {
        ftw = new FilteredTableWrapper<>(table, filterField);

        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        descriptionColumn.setCellValueFactory(new PropertyValueFactory<>("description"));
        startWeekColumn.setCellValueFactory(new PropertyValueFactory<>("startWeek"));
        deadlineWeekColumn.setCellValueFactory(new PropertyValueFactory<>("deadlineWeek"));

        addTableDeselect(table);
        addFieldNumber(idField);
        addFieldNumber(startWeekField);
        addFieldNumber(deadlineWeekField);
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
        Iterable<Assignment> elements = service.getAssignments();
        ftw.setTableData(listFromIterable(elements));
    }

    private void setButtonsDisable(boolean disabled) {
        updateButton.setDisable(disabled);
        deleteButton.setDisable(disabled);
    }

    private void setFieldsData(String id, String description, String startWeekString, String deadlineWeekString) {
        idField.setText(id);
        descriptionField.setText(description);
        startWeekField.setText(startWeekString);
        deadlineWeekField.setText(deadlineWeekString);
    }

    private void setFieldsData() {
        setFieldsData("", "", "", "");
    }

    private void setFieldsData(Assignment assignment) {
        setFieldsData(assignment.getId(), assignment.getDescription(),
                assignment.getStartWeekString(), assignment.getDeadlineWeekString());
    }

    @FXML
    void onFilterFieldAction(ActionEvent event) {
        loadTableData();
    }

    @FXML
    void onAddButtonAction(ActionEvent event) {
        if (startWeekField.getText().isEmpty()) {
            showErrorAlert("Start week field cannot be empty");
            return;
        }

        if (deadlineWeekField.getText().isEmpty()) {
            showErrorAlert("Deadline week field cannot be empty");
            return;
        }

        try {
            Assignment assignment = service.addAssignment(idField.getText(), descriptionField.getText(),
                    Long.parseLong(startWeekField.getText()), Long.parseLong(deadlineWeekField.getText()));
            ftw.setSelected(assignment);
        } catch (CommonServiceException | ValidationException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @FXML
    void onDeleteButtonAction(ActionEvent event) {
        Assignment assignment = ftw.getSelected();
        if (assignment == null) {
            showErrorAlert("No assignment selected!");
            return;
        }

        try {
            service.deleteAssignment(assignment.getId());
        } catch (CommonServiceException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @FXML
    void onUpdateButtonAction(ActionEvent event) {
        Assignment assignment = ftw.getSelected();
        if (assignment == null) {
            showErrorAlert("No assignment selected!");
            return;
        }

        try {
            service.updateAssignment(assignment.getId(), descriptionField.getText(),
                    Long.parseLong(startWeekField.getText()), Long.parseLong(deadlineWeekField.getText()));
        } catch (CommonServiceException | ValidationException e) {
            showErrorAlert(e.getMessage());
        }
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        if ("assignments".equals(key)) {
            loadTableData();
        }
    }
}
