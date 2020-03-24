package repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public abstract class DatabaseRepository {
    protected final Connection connection;
    protected final Logger logger = LogManager.getLogger();

    public DatabaseRepository(Connection connection) throws RepositoryError {
        this.connection = connection;

        createTable();
    }

    public abstract void createTable() throws RepositoryError;

    protected boolean isTableCreated(String tableName) {
        try {
            ResultSet res = connection.getMetaData().getTables(null, null,
                    tableName, new String[]{"TABLE"});
            return res.next();
        } catch (SQLException ex) {
            return false;
        }
    }
}
