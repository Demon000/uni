package controller;

import domain.Arbiter;
import domain.Score;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import observer.Observer;
import repository.RepositoryError;
import service.Service;
import utils.StringUtils;

import java.util.Collection;
import java.util.List;

import static utils.FxUtils.*;

public class ArbiterController implements Observer {
    public static final String VIEW_NAME = "/ArbiterView.fxml";
    public static final String VIEW_TITLE = "Arbiter";

    private final Service service;
    private Arbiter arbiter;

    @FXML
    private TableView<Score> participantsTable;

    @FXML
    private TableColumn<Score, String> participantsNameColumn;

    @FXML
    private TableColumn<Score, Integer> participantsTypeScoreColumn;

    @FXML
    private TableColumn<Score, Integer> participantsTotalScoreColumn;

    @FXML
    private TableView<Score> rankingTable;

    @FXML
    private TableColumn<Score, String> rankingNameColumn;

    @FXML
    private TableColumn<Score, Integer> rankingScoreColumn;

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
        addTableDeselect(participantsTable);
        addTableUnselectable(rankingTable);
        setRankingsTableVisibility(false);

        participantsTypeScoreColumn.setText(String.format("%s score",
                StringUtils.toTitleCase(arbiter.getType().toString())));
        participantsNameColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(score.getParticipant().getName());
        });
        participantsTypeScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getScore(arbiter.getType()));
        });
        participantsTotalScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getTotalScore());
        });
        participantsTable.getSortOrder().add(participantsNameColumn);
        participantsTable.sort();

        rankingNameColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(score.getParticipant().getName());
        });

        rankingScoreColumn.setSortType(TableColumn.SortType.DESCENDING);
        rankingScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getScore(arbiter.getType()));
        });
        rankingTable.getSortOrder().add(rankingScoreColumn);
        rankingTable.sort();

        participantsTable.getSelectionModel().selectedItemProperty().addListener((obs, oldSelection, newSelection) -> {
            onSelectionChanged();
        });

        loadTablesData();

        service.addObserver(this);
    }

    public void setRankingsTableVisibility(boolean visible) {
        rankingTable.setManaged(visible);
        rankingTable.setVisible(visible);
    }

    public Score getSelected() {
        return participantsTable.getSelectionModel().getSelectedItem();
    }

    public Score findScoreInTable(TableView<Score> table, Score score) {
        Collection<Score> scores = table.getItems();
        for (Score s : scores) {
            if (s.getParticipant().getId() == score.getParticipant().getId()) {
                return s;
            }
        }

        return null;
    }

    public void setParticipantsScore(Score score) {
        Score scoreItem = findScoreInTable(participantsTable, score);
        if (scoreItem != null) {
            scoreItem.setScores(score.getScores());
        }

        participantsTable.refresh();
    }

    public void setRankingScore(Score score) {
        Score scoreItem = findScoreInTable(rankingTable, score);

        boolean isZeroScore = score.getScore(arbiter.getType()) == 0;
        boolean isNullItem = scoreItem == null;
        if (isZeroScore && !isNullItem) {
            rankingTable.getItems().remove(scoreItem);
        } else if (!isZeroScore && !isNullItem) {
            scoreItem.setScores(score.getScores());
        } else if (!isZeroScore) {
            rankingTable.getItems().add(score);
        }

        participantsTable.refresh();
        rankingTable.sort();
    }

    public void setScore(Score score) {
        setParticipantsScore(score);
        setRankingScore(score);
    }

    private void loadParticipantsTableData() {
        List<Score> scores;
        try {
            scores = service.getScores();
        } catch (RepositoryError e) {
            showErrorAlert(e.getMessage());
            return;
        }

        participantsTable.getItems().setAll(scores);
    }

    private void loadRankingTableData() {
        List<Score> scores;
        try {
            scores = service.getScoresForType(arbiter.getType());
        } catch (RepositoryError e) {
            showErrorAlert(e.getMessage());
            return;
        }

        rankingTable.getItems().setAll(scores);
    }

    private void loadTablesData() {
        loadParticipantsTableData();
        loadRankingTableData();
    }

    void onSelectionChanged() {
        Score selected = getSelected();
        if (selected == null) {
            setButton.setDisable(true);
            pointsField.setText("");
        } else {
            setButton.setDisable(false);
            pointsField.setText(String.valueOf(selected.getScore(arbiter.getType())));
        }
    }

    @FXML
    void onSetButtonAction(ActionEvent event) {
        Score selected = getSelected();
        try {
            selected.setScore(arbiter.getType(), Integer.parseInt(pointsField.getText()));
            service.setScore(selected, arbiter);
        } catch (RepositoryError e) {
            showErrorAlert(e.getMessage());
        }
    }

    @FXML
    void onRefreshButtonAction(ActionEvent event) {
        loadTablesData();
    }

    @FXML
    void onShowRankingsButtonAction(ActionEvent event) {
        setRankingsTableVisibility(showRankingsButton.isSelected());
    }

    @Override
    public void onChange(String key, Object oldValue, Object newValue) {
        switch (key) {
        case Service.SCORE_SET_CHANGE:
                Score score = (Score) newValue;
                setScore(score);
            break;
        default:
            break;
        }
    }
}
