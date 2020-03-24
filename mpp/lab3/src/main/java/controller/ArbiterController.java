package controller;

import domain.Arbiter;
import domain.Participant;
import domain.ParticipantScore;
import javafx.beans.property.ReadOnlyIntegerWrapper;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import repository.RepositoryError;
import service.Service;

import java.util.List;

import static utils.FxUtils.*;

public class ArbiterController {
    public static final String VIEW_NAME = "/ArbiterView.fxml";
    public static final String VIEW_TITLE = "Arbiter";

    private final Service service;
    private Arbiter arbiter;

    @FXML
    private TableView<ParticipantScore> participantTotalScoreTable;

    @FXML
    private TableColumn<ParticipantScore, String> participantTotalScoreNameColumn;

    @FXML
    private TableColumn<ParticipantScore, Integer> participantTotalScoreColumn;

    @FXML
    private TableView<ParticipantScore> participantTypeScoreTable;

    @FXML
    private TableColumn<ParticipantScore, String> participantTypeScoreNameColumn;

    @FXML
    private TableColumn<ParticipantScore, Integer> participantTypeScoreColumn;

    @FXML
    private TextField pointsField;

    @FXML
    private Button setButton;

    @FXML
    private ToggleButton showRankingsButton;

    @FXML
    private Label arbiterNameField;

    @FXML
    private Label arbiterTypeField;

    public ArbiterController(Service service, Arbiter arbiter) {
        this.service = service;
        this.arbiter = arbiter;
    }

    @FXML
    public void initialize() {
        this.arbiterNameField.setText(arbiter.getName());
        this.arbiterTypeField.setText(arbiter.getType().toString().toLowerCase());

        addFieldNumber(pointsField);

        participantTotalScoreNameColumn.setCellValueFactory(scoreCellDataFeatures -> {
            ParticipantScore score = scoreCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(score.getParticipant().getName());
        });
        participantTotalScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            ParticipantScore score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getTotalScore());
        });

        participantTypeScoreNameColumn.setCellValueFactory(scoreCellDataFeatures -> {
            ParticipantScore score = scoreCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(score.getParticipant().getName());
        });
        participantTypeScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            ParticipantScore score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getScore(arbiter.getType()));
        });

        participantTypeScoreTable.setSelectionModel(null);

        participantTotalScoreTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            onSelectionChanged();
        });

        setRankingsTableVisibility(false);
        addTableDeselect(participantTotalScoreTable);

        loadTablesData();
    }

    public ParticipantScore getSelected() {
        return participantTotalScoreTable.getSelectionModel().getSelectedItem();
    }

    public void setSelected(ParticipantScore newSelected) {
        participantTotalScoreTable.getItems().forEach(element -> {
            if (element.getParticipant().getId() == newSelected.getParticipant().getId()) {
                participantTotalScoreTable.getSelectionModel().select(element);
            }
        });
    }

    public void setRankingsTableVisibility(boolean visible) {
        if (visible) {
            loadTypeScoreTableData();
        }
        participantTypeScoreTable.setManaged(visible);
        participantTypeScoreTable.setVisible(visible);
    }

    void onSelectionChanged() {
        ParticipantScore selected = getSelected();
        if (selected != null) {
            setButton.setDisable(false);
            pointsField.setText(String.valueOf(selected.getScore(arbiter.getType())));
        } else {
            setButton.setDisable(true);
            pointsField.setText("");
        }
    }

    private void loadTotalScoreTableData() {
        ParticipantScore lastSelected = getSelected();

        List<ParticipantScore> scores;
        try {
            scores = service.getScores();
        } catch (RepositoryError e) {
            e.printStackTrace();
            return;
        }

        participantTotalScoreTable.getItems().setAll(scores);

        if (lastSelected != null) {
            setSelected(lastSelected);
        }
    }

    private void loadTypeScoreTableData() {
        List<ParticipantScore> scores;
        try {
            scores = service.getScoresForType(arbiter.getType());
        } catch (RepositoryError e) {
            e.printStackTrace();
            return;
        }

        participantTypeScoreTable.getItems().setAll(scores);
    }

    private void loadTablesData() {
        loadTotalScoreTableData();
        if (showRankingsButton.isSelected()) {
            loadTypeScoreTableData();
        }
    }

    @FXML
    void onSetButtonAction(ActionEvent event) {
        ParticipantScore selected = getSelected();
        try {
            service.setScore(selected.getParticipant(), arbiter, Integer.parseInt(pointsField.getText()));
        } catch (RepositoryError e) {
            e.printStackTrace();
            return;
        }

        loadTablesData();
    }

    @FXML
    void onShowRankingsButtonAction(ActionEvent event) {
        setRankingsTableVisibility(showRankingsButton.isSelected());
    }
}
