package repository;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.lang.reflect.InvocationTargetException;
import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class DatabaseRepository<E> implements IRepository<E> {
    protected final DatabaseTableMetadata<E> tableMetadata;
    protected final Connection connection;
    private Logger logger;
    protected final Class<E> clazz;

    public DatabaseRepository(Class<E> clazz, Connection connection) throws DatabaseError {
        this.clazz = clazz;
        this.connection = connection;
        this.tableMetadata = new DatabaseTableMetadata<>(clazz);
        this.logger = LogManager.getLogger();

        if (!isTableCreated()) {
            createTable();
        }
    }

    protected boolean isTableCreated() {
        try {
            ResultSet res = connection.getMetaData().getTables(null, null,
                    tableMetadata.getTableName(), new String[]{"TABLE"});
            return res.next();
        } catch (SQLException ex) {
            logger.error(ex);
            return false;
        }
    }

    protected void createTable() throws DatabaseError {
        String tableName = tableMetadata.getTableName();

        List<String> parts = new ArrayList<>(tableMetadata.getFieldsCreationList());

        String primaryKeysCreationString = tableMetadata.getPrimaryKeysConstraint();
        if (primaryKeysCreationString != null) {
            parts.add(primaryKeysCreationString);
        }

        parts.addAll(tableMetadata.getForeignKeyConstraints());

        String command = String.format("create table %s (%s);",
                tableName,
                String.join(", ", parts));

        try {
            Statement statement = connection.createStatement();
            statement.execute(command);
            logger.info(command);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DatabaseError(ex);
        }
    }

    public void add(E e) throws DatabaseError {
        Collection<DatabaseFieldMetadata> allFields = tableMetadata.getFields();

        String command = String.format("insert into %s (%s) values (%s);",
                tableMetadata.getTableName(),
                tableMetadata.getFieldNames(allFields, ", "),
                tableMetadata.getFieldsPlaceholder(allFields, ", "));

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            tableMetadata.setStatementFieldValues(e, statement, allFields);
            statement.executeUpdate();
            logger.info(command);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DatabaseError(ex);
        }
    }

    protected E getOneFromResults(ResultSet results) throws DatabaseError, SQLException {
        ResultSetMetaData metadata = results.getMetaData();
        E e;
        try {
            e = clazz.getDeclaredConstructor().newInstance();
        } catch (InstantiationException | IllegalAccessException
                | NoSuchMethodException | InvocationTargetException ex) {
            throw new DatabaseError(ex);
        }

        for (int i = 1; i <= metadata.getColumnCount(); i++) {
            tableMetadata.getFieldByName(metadata.getColumnName(i)).setValue(e, results.getObject(i));
        }

        return e;
    }

    protected List<E> getFromResults(ResultSet results) throws DatabaseError, SQLException {
        List<E> entities = new ArrayList<>();
        while (results.next()) {
            E e = getOneFromResults(results);
            entities.add(e);
        }

        return entities;
    }

    public List<E> find() throws DatabaseError {
        Collection<DatabaseFieldMetadata> allFields = tableMetadata.getFields();

        String command = String.format("select %s from %s;",
                tableMetadata.getFieldNames(allFields, ", "),
                tableMetadata.getTableName());

        try {
            Statement statement = connection.createStatement();
            ResultSet results = statement.executeQuery(command);
            logger.info(command);
            return getFromResults(results);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DatabaseError(ex);
        }
    }

    public E findById(E e) throws DatabaseError {
        Collection<DatabaseFieldMetadata> primaryFields = tableMetadata.getPrimaryKeyFields();
        Collection<DatabaseFieldMetadata> allFields = tableMetadata.getFields();

        String command = String.format("select %s from %s where %s;",
                tableMetadata.getFieldNames(allFields, ", "),
                tableMetadata.getTableName(),
                tableMetadata.getFieldsEqualPlaceholders(primaryFields, " and "));

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            tableMetadata.setStatementFieldValues(e, statement, primaryFields);
            ResultSet results = statement.executeQuery();
            logger.info(command);
            return getOneFromResults(results);
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DatabaseError(ex);
        }
    }

    public void update(E e) throws DatabaseError {
        Collection<DatabaseFieldMetadata> updatedFields = tableMetadata.getFields(f -> !f.isPrimaryKey());
        Collection<DatabaseFieldMetadata> primaryFields = tableMetadata.getPrimaryKeyFields();
        if (updatedFields.size() == 0) {
            throw new DatabaseError("DatabaseTable has no fields to be updated");
        }

        String command = String.format("update %s set %s where %s;",
                tableMetadata.getTableName(),
                tableMetadata.getFieldsEqualPlaceholders(updatedFields, ", "),
                tableMetadata.getFieldsEqualPlaceholders(primaryFields, " and "));

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            int i = tableMetadata.setStatementFieldValues(e, statement, updatedFields);
            tableMetadata.setStatementFieldValues(e, statement, primaryFields, i);
            logger.info(command);
            statement.executeUpdate();
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DatabaseError(ex);
        }
    }

    public void delete(E e) throws DatabaseError {
        Collection<DatabaseFieldMetadata> primaryFields = tableMetadata.getPrimaryKeyFields();

        String command = String.format("delete from %s where %s;",
                tableMetadata.getTableName(),
                tableMetadata.getFieldsEqualPlaceholders(primaryFields, " and "));

        try {
            PreparedStatement statement = connection.prepareStatement(command);
            tableMetadata.setStatementFieldValues(e, statement, primaryFields);
            logger.info(command);
            statement.executeUpdate();
        } catch (SQLException ex) {
            logger.error(ex);
            throw new DatabaseError(ex);
        }
    }
}
