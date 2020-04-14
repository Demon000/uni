package controller;

import domain.Arbiter;
import domain.Score;
import javafx.application.Platform;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import service.IService;
import service.IServiceObserver;
import service.ServiceError;
import utils.StringUtils;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Collection;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static utils.FxUtils.*;

public class ArbiterController implements IServiceObserver {
    public static final String VIEW_NAME = "/ArbiterView.fxml";
    public static final String VIEW_TITLE = "Arbiter";

    ExecutorService executor = Executors.newFixedThreadPool(10);
    private final IService service;
    private final Arbiter arbiter;

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

    public ArbiterController(IService service, Arbiter arbiter) {
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

        participantsTable.getSelectionModel().selectedItemProperty().addListener(
                (obs, oldSelection, newSelection) -> onSelectionChanged());

        getTableData();

        try {
            IServiceObserver observer = (IServiceObserver) UnicastRemoteObject.exportObject(this, 0);
            service.addObserver(observer);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    public void stop() {
        executor.shutdownNow();
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

    private void getParticipantsTableData() {
        executor.execute(() -> {
            try {
                List<Score> scores = service.getScores();
                Platform.runLater(() -> setParticipantsTableData(scores));
            } catch (ServiceError | RemoteException e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
    }

    private void getRankingTableData() {
        executor.execute(() -> {
            try {
                List<Score> scores = service.getScoresForType(arbiter.getType());
                Platform.runLater(() -> setRankingTableData(scores));
            } catch (ServiceError | RemoteException e) {
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
                        arbiter.getType(), Integer.parseInt(pointsField.getText()));
            } catch (ServiceError | RemoteException e) {
                Platform.runLater(() -> showErrorAlert(e));
            }
        });
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
}
