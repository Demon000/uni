package controller;

import domain.Arbiter;
import domain.Score;
import javafx.application.Platform;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import service.IService;
import service.IServiceObserver;
import service.ServiceConnectionStatus;
import service.ServiceError;
import utils.StringUtils;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Collection;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static utils.FxUtils.*;

public class ArbiterController implements IServiceObserver, IController {
    @Override
    public String getStageTitle() {
        return "Arbiter";
    }

    @Override
    public String getFXMLFilePath() {
        return "/ArbiterView.fxml";
    }

    ExecutorService executor = Executors.newFixedThreadPool(10);
    private final IService service;

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

    @FXML
    private HBox connectionBox;

    public ArbiterController(IService service) {
        this.service = service;
    }

    @FXML
    public void initialize() {
        addFieldNumber(pointsField);
        addTableDeselect(participantsTable);
        addTableUnselectable(rankingTable);
        setRankingsTableVisibility(false);

        participantsNameColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyStringWrapper(score.getParticipant().getName());
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
        rankingTable.getSortOrder().add(rankingScoreColumn);
        rankingTable.sort();

        participantsTable.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldSelection, newSelection) -> onSelectionChanged());

        service.addObserver(this);
    }

    public void onWindowShow() {
        Arbiter arbiter = service.getLoggedInArbiter();
        if (arbiter == null) {
            return;
        }

        this.arbiterNameField.setText(arbiter.getName());
        this.arbiterTypeField.setText(arbiter.getType().toString().toLowerCase());
        participantsTypeScoreColumn.setText(String.format("%s score",
                StringUtils.toTitleCase(arbiter.getType().toString())));
        participantsTypeScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getScore(arbiter.getType()));
        });
        rankingScoreColumn.setCellValueFactory(scoreCellDataFeatures -> {
            Score score = scoreCellDataFeatures.getValue();
            return new ReadOnlyObjectWrapper<>(score.getScore(arbiter.getType()));
        });
        setConnectionBoxVisibility();
        getTableData();
    }

    public void stop() {
        executor.shutdown();
        service.removeObserver(this);
    }

    private void setConnectionBoxVisibility(boolean visible) {
        connectionBox.setManaged(visible);
        connectionBox.setVisible(visible);
    }

    private void setConnectionBoxVisibility(ServiceConnectionStatus status) {
        setConnectionBoxVisibility(status != ServiceConnectionStatus.CONNECTED);
    }

    private void setConnectionBoxVisibility() {
        setConnectionBoxVisibility(service.getConnectionStatus());
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
        Arbiter arbiter = service.getLoggedInArbiter();
        if (arbiter == null) {
            return;
        }

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

    private void getParticipantsTableData() {
        executor.execute(() -> {
            try {
                List<Score> scores = service.getScores();
                Platform.runLater(() -> setParticipantsTableData(scores));
            } catch (ServiceError e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
    }

    private void getRankingTableData() {
        executor.execute(() -> {
            try {
                List<Score> scores = service.getRankings();
                Platform.runLater(() -> setRankingTableData(scores));
            } catch (ServiceError e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
    }

    private void getTableData() {
        getParticipantsTableData();
        getRankingTableData();
    }

    private void setParticipantsTableData(List<Score> scores) {
        participantsTable.getItems().setAll(scores);
    }

    private void setRankingTableData(List<Score> scores) {
        rankingTable.getItems().setAll(scores);
    }

    void onSelectionChanged() {
        Arbiter arbiter = service.getLoggedInArbiter();
        if (arbiter == null) {
            return;
        }

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
        executor.execute(() -> {
            try {
                service.setScoreValue(getSelected().getParticipant().getId(),
                        Integer.parseInt(pointsField.getText()));
            } catch (ServiceError e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
    }

    @FXML
    void onRetryButtonAction(ActionEvent event) {
        service.ping();
    }

    @FXML
    void onRefreshButtonAction(ActionEvent event) {
        getTableData();
    }

    @FXML
    void onShowRankingsButtonAction(ActionEvent event) {
        setRankingsTableVisibility(showRankingsButton.isSelected());
    }

    @Override
    public void onSetScore(Score score) {
        Platform.runLater(() -> setScore(score));
    }

    @Override
    public void onConnectionStatusChange(ServiceConnectionStatus status) {
        Platform.runLater(() -> setConnectionBoxVisibility(status));
    }
}
