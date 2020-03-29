package repository;

import domain.Participant;

import java.sql.*;

public class ParticipantRepository extends DatabaseRepository
        implements IParticipantRepository {
    public ParticipantRepository(Connection connection) throws RepositoryError {
        super(connection);
    }

    @Override
    public void createTable() throws RepositoryError {
        if (isTableCreated("Participants")) {
            return;
        }

        String command =
                "create table Participants(" +
                    "ParticipantId integer primary key autoincrement, " +
                    "ParticipantName nvarchar(255) not null unique" +
                ");";

        try {
            Statement statement = connection.createStatement();
            statement.execute(command);
            logger.info("Created table Participants");
            logger.info(command);
        } catch (SQLException e) {
            logger.error("Failed to create table Participants");
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public void add(Participant participant) throws RepositoryError {
        String command =
                "insert into Participants (" +
                    "ParticipantName" +
                ") values (" +
                    "?" +
                ");";

        try {
            PreparedStatement statement = connection.prepareStatement(command, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, participant.getName());
            statement.executeUpdate();

            ResultSet results = statement.getGeneratedKeys();
            if (results.next()) {
                participant.setId(results.getInt(1));
            } else {
                throw new RepositoryError("Failed to retrieve generated keys");
            }

            logger.info("Added participant");
            logger.info(command);
        } catch (SQLException e) {
            logger.error("Failed to add participant");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }
}
