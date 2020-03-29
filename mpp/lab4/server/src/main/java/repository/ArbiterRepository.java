package repository;

import domain.Arbiter;
import domain.ScoreType;

import java.sql.*;

public class ArbiterRepository extends DatabaseRepository
        implements IArbiterRepository {
    public ArbiterRepository(Connection connection) throws RepositoryError {
        super(connection);
    }

    @Override
    public void createTable() throws RepositoryError {
        if (isTableCreated("Arbiters")) {
            return;
        }

        String command =
                "create table Arbiters (" +
                    "ArbiterId integer primary key autoincrement, " +
                    "ArbiterName nvarchar(255) not null unique, " +
                    "ArbiterPassword nvarchar(255) not null, " +
                    "ArbiterType integer not null" +
                ");";

        try {
            Statement statement = connection.createStatement();
            statement.execute(command);
            logger.info("Created table Arbiters");
            logger.info(command);
        } catch (SQLException e) {
            logger.error("Failed to create table Arbiters");
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public void add(Arbiter arbiter) throws RepositoryError {
        String command =
                "insert into Arbiters (" +
                    "ArbiterName, " +
                    "ArbiterPassword, " +
                    "ArbiterType" +
                ") values (" +
                    "?, " +
                    "?, " +
                    "?" +
                ");";

        try {
            PreparedStatement statement = connection.prepareStatement(command, Statement.RETURN_GENERATED_KEYS);
            statement.setString(1, arbiter.getName());
            statement.setString(2, arbiter.getPassword());
            statement.setInt(3, arbiter.getType().ordinal());
            statement.executeUpdate();

            ResultSet results = statement.getGeneratedKeys();
            if (results.next()) {
                arbiter.setId(results.getInt(1));
            } else {
                throw new RepositoryError("Failed to retrieve generated keys");
            }

            logger.info("Added arbiter");
            logger.info(command);
        } catch (RepositoryError | SQLException e) {
            logger.error("Failed to add arbiter");
            logger.error(command);
            logger.error(e);
            throw new RepositoryError(e);
        }
    }

    @Override
    public Arbiter findByNameAndPassword(String name, String password) throws RepositoryError {
        String command =
                "select " +
                    "ArbiterId, " +
                    "ArbiterType " +
                "from Arbiters where " +
                    "ArbiterName=? and " +
                    "ArbiterPassword=?" +
                ";";

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            statement.setString(1, name);
            statement.setString(2, password);
            ResultSet results = statement.executeQuery();

            Arbiter arbiter;
            if (results.next()) {
                int id = results.getInt(1);
                ScoreType type = ScoreType.values()[results.getInt(2)];
                arbiter = new Arbiter(id, name, password, type);
            } else {
                throw new RepositoryError("Failed to retrieve arbiter");
            }

            logger.info("Retrieved arbiter");
            logger.info(command);

            return arbiter;
        } catch (RepositoryError | SQLException e) {
            logger.error("Failed to retrieve arbiter");
            logger.error(e);
            throw new RepositoryError(e);
        }
    }
}
