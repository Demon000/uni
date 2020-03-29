package repository;

import domain.Participant;
import domain.Score;
import domain.ScoreType;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ScoreRepository extends DatabaseRepository
        implements IScoreRepository {
    public ScoreRepository(Connection connection) throws RepositoryError {
        super(connection);
    }

    @Override
    public void createTable() throws RepositoryError {
        if (isTableCreated("Scores")) {
            return;
        }

        String command =
                "create table Scores(" +
                    "ParticipantId integer not null, " +
                    "ScoreType integer not null, " +
                    "ScoreValue integer not null, " +
                    "primary key(ParticipantId, ScoreType), " +
                    "foreign key(ParticipantId) references Participants(ParticipantId)" +
                ");";

        try {
            Statement statement = connection.createStatement();
            statement.execute(command);
            logger.info("Created table Scores");
            logger.info(command);
        } catch (SQLException e) {
            logger.error("Failed to create table Scores");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public void addScore(int participantId, ScoreType type, int score) throws RepositoryError {
        String command =
                "insert into Scores (" +
                    "ParticipantId, " +
                    "ScoreType, " +
                    "ScoreValue" +
                ") values (" +
                    "?, " +
                    "?, " +
                    "?" +
                ");";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, participantId);
            statement.setInt(2, type.ordinal());
            statement.setInt(3, score);
            statement.executeUpdate();
            logger.info("Added score");
            logger.info(command);
        } catch (SQLException e) {
            logger.error("Failed to add score");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public Score getScore(int participantId) throws RepositoryError {
        String command =
                "select " +
                    "P.ParticipantName, " +
                    "sum(case when S.ScoreType=? then S.ScoreValue else 0 end), " +
                    "sum(case when S.ScoreType=? then S.ScoreValue else 0 end), " +
                    "sum(case when S.ScoreType=? then S.ScoreValue else 0 end) " +
                "from Participants P " +
                "left outer join Scores S on S.ParticipantId=P.ParticipantId " +
                "where P.ParticipantId=? " +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, ScoreType.CYCLING.ordinal());
            statement.setInt(2, ScoreType.RUNNING.ordinal());
            statement.setInt(3, ScoreType.SWIMMING.ordinal());
            statement.setInt(4, participantId);
            ResultSet results = statement.executeQuery();

            Score score;
            if (results.next()) {
                String name = results.getString(1);

                Participant participant = new Participant(participantId, name);
                score = new Score(participant);

                score.setScore(ScoreType.CYCLING, results.getInt(2));
                score.setScore(ScoreType.RUNNING, results.getInt(3));
                score.setScore(ScoreType.SWIMMING, results.getInt(4));
            } else {
                throw new RepositoryError("Failed to retrieve total score by id");
            }

            logger.info("Retrieved total score by id");
            logger.info(command);
            return score;
        } catch (RepositoryError | SQLException e) {
            logger.error("Failed to retrieve total score by id");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public void updateScore(int participantId, ScoreType type, int score) throws RepositoryError {
        String command =
                "update Scores set " +
                    "ScoreValue=? " +
                "where " +
                    "ParticipantId=? and " +
                    "ScoreType=?" +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, score);
            statement.setInt(2, participantId);
            statement.setInt(3, type.ordinal());
            statement.executeUpdate();
            logger.info("Updated score");
            logger.info(command);
        } catch (SQLException ex) {
            logger.error("Failed to update score");
            logger.error(command);
            logger.error(ex);
            throw new RepositoryError(ex);
        }
    }

    @Override
    public void setScore(int participantId, ScoreType type, int score) throws RepositoryError {
        try {
            addScore(participantId, type, score);
            return;
        } catch (RepositoryError ignored) {
        }

        updateScore(participantId, type, score);
    }

    @Override
    public List<Score> findScoresSortedByName() throws RepositoryError {
        String command =
                "select " +
                    "P.ParticipantId, " +
                    "P.ParticipantName, " +
                    "sum(case when S.ScoreType=? then S.ScoreValue else 0 end), " +
                    "sum(case when S.ScoreType=? then S.ScoreValue else 0 end), " +
                    "sum(case when S.ScoreType=? then S.ScoreValue else 0 end) " +
                "from Participants P " +
                "left outer join Scores S on S.ParticipantId=P.ParticipantId " +
                "group by P.ParticipantId, P.ParticipantName " +
                "order by P.ParticipantName " +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, ScoreType.CYCLING.ordinal());
            statement.setInt(2, ScoreType.RUNNING.ordinal());
            statement.setInt(3, ScoreType.SWIMMING.ordinal());
            ResultSet results = statement.executeQuery();
            List<Score> scores = new ArrayList<>();

            while (results.next()) {
                int id = results.getInt(1);
                String name = results.getString(2);

                Participant participant = new Participant(id, name);
                Score score = new Score(participant);

                score.setScore(ScoreType.CYCLING, results.getInt(3));
                score.setScore(ScoreType.RUNNING, results.getInt(4));
                score.setScore(ScoreType.SWIMMING, results.getInt(5));

                scores.add(score);
            }

            logger.info("Retrieved total score sorted by name");
            logger.info(command);
            return scores;
        } catch (SQLException e) {
            logger.error("Failed to retrieve total score sorted by name");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public List<Score> findScoresForTypeSortedDescending(ScoreType type) throws RepositoryError {
        String command =
                "select " +
                    "P.ParticipantId, " +
                    "P.ParticipantName, " +
                    "S.ScoreValue " +
                "from Scores S " +
                "inner join Participants P on S.ParticipantId=P.ParticipantId " +
                "where S.ScoreType=? and S.ScoreValue is not 0 " +
                "order by S.ScoreValue desc " +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, type.ordinal());
            ResultSet results = statement.executeQuery();
            List<Score> scores = new ArrayList<>();

            while (results.next()) {
                int id = results.getInt(1);
                String name = results.getString(2);

                Participant participant = new Participant(id, name);
                Score score = new Score(participant);

                score.setScore(type, results.getInt(3));

                scores.add(score);
            }

            logger.info("Retrieved scores for type sorted descending");
            logger.info(command);
            return scores;
        } catch (SQLException e) {
            logger.error("Failed to retrieve scores for type sorted descending");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }
}
