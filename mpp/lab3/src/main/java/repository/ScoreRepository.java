package repository;

import domain.Participant;
import domain.ParticipantScore;
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
                    "ArbiterId integer not null, " +
                    "Value integer not null, " +
                    "primary key(ParticipantId, ArbiterId), " +
                    "foreign key(ParticipantId) references Participants(ParticipantId), " +
                    "foreign key(ArbiterId) references Arbiters(ArbiterId)" +
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
    public void addScore(int participantId, int arbiterId, int score) throws RepositoryError {
        String command =
                "insert into Scores (" +
                    "ParticipantId, " +
                    "ArbiterId, " +
                    "Value" +
                ") values (" +
                    "?, " +
                    "?, " +
                    "?" +
                ");";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, participantId);
            statement.setInt(2, arbiterId);
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
    public void updateScore(int participantId, int arbiterId, int score) throws RepositoryError {
        String command =
                "update Scores set " +
                    "Value=? " +
                "where " +
                    "ParticipantId=? and " +
                    "ArbiterId=?" +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, score);
            statement.setInt(2, participantId);
            statement.setInt(3, arbiterId);
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
    public void setScore(int participantId, int arbiterId, int score) throws RepositoryError {
        try {
            addScore(participantId, arbiterId, score);
            return;
        } catch (RepositoryError ignored) {
        }

        updateScore(participantId, arbiterId, score);
    }

    @Override
    public List<ParticipantScore> findScoresSortedByName() throws RepositoryError {
        String command =
                "select " +
                    "P.ParticipantId, " +
                    "P.ParticipantName, " +
                    "sum(case when A.ArbiterType=? then S.Value else 0 end), " +
                    "sum(case when A.ArbiterType=? then S.Value else 0 end), " +
                    "sum(case when A.ArbiterType=? then S.Value else 0 end) " +
                "from Participants P " +
                "left outer join Scores S on S.ParticipantId=P.ParticipantId " +
                "left outer join Arbiters A on A.ArbiterId=S.ArbiterId " +
                "group by P.ParticipantId, P.ParticipantName " +
                "order by P.ParticipantName " +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, ScoreType.CYCLING.ordinal());
            statement.setInt(2, ScoreType.RUNNING.ordinal());
            statement.setInt(3, ScoreType.SWIMMING.ordinal());
            ResultSet results = statement.executeQuery();
            List<ParticipantScore> scores = new ArrayList<>();

            while (results.next()) {
                int id = results.getInt(1);
                String name = results.getString(2);

                Participant participant = new Participant(id, name);
                ParticipantScore score = new ParticipantScore(participant);

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
    public List<ParticipantScore> findScoresForTypeSortedDescending(ScoreType type) throws RepositoryError {
        String command =
                "select " +
                    "P.ParticipantId, " +
                    "P.ParticipantName, " +
                    "S.Value " +
                "from Scores S " +
                "inner join Participants P on S.ParticipantId=P.ParticipantId " +
                "inner join Arbiters A on S.ArbiterId = A.ArbiterId " +
                "where A.ArbiterType=?" +
                "order by S.Value desc " +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setInt(1, type.ordinal());
            ResultSet results = statement.executeQuery();
            List<ParticipantScore> scores = new ArrayList<>();

            while (results.next()) {
                int id = results.getInt(1);
                String name = results.getString(2);

                Participant participant = new Participant(id, name);
                ParticipantScore score = new ParticipantScore(participant);

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
