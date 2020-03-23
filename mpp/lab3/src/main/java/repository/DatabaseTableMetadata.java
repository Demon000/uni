package repository;

import java.lang.reflect.Field;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.*;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class DatabaseTableMetadata<E> {
    private final Map<String, DatabaseFieldMetadata> nameToFieldMap = new HashMap<>();
    private final String tableName;

    public DatabaseTableMetadata(Class<E> clazz) throws DatabaseError {
        DatabaseTable dt = clazz.getAnnotation(DatabaseTable.class);
        if (dt == null) {
            throw new DatabaseError("Failed to find DatabaseTable annotation on generic parameter type");
        }

        this.tableName = dt.name();

        for (Field field : clazz.getDeclaredFields()) {
            DatabaseFieldMetadata fieldMetadata;

            try {
                fieldMetadata = new DatabaseFieldMetadata(field);
            } catch (DatabaseError databaseError) {
                continue;
            }

            nameToFieldMap.put(fieldMetadata.getName(), fieldMetadata);
        }

    }

    public List<String> getFieldsCreationList() {
        return getFields().stream()
                .map(DatabaseFieldMetadata::getFieldCreationString)
                .collect(Collectors.toList());
    }

    public List<String> getForeignKeyConstraints() {
        return getFields(f -> !f.getForeignKey().isEmpty()).stream()
                .map(DatabaseFieldMetadata::getForeignKeyConstraint)
                .collect(Collectors.toList());
    }

    public String getPrimaryKeysConstraint() {
        Collection<DatabaseFieldMetadata> primaryFields = getPrimaryKeyFields();
        if (primaryFields.size() == 0) {
            return null;
        }

        return String.format("primary key (%s)", getFieldNames(primaryFields, ", "));
    }

    public String getTableName() {
        return tableName;
    }

    public Collection<DatabaseFieldMetadata> getFields() {
        return nameToFieldMap.values();
    }

    public Collection<DatabaseFieldMetadata> getFields(Predicate<DatabaseFieldMetadata> fn) {
        return getFields().stream().filter(fn).collect(Collectors.toList());
    }

    public Collection<DatabaseFieldMetadata> getPrimaryKeyFields() {
        return getFields(DatabaseFieldMetadata::isPrimaryKey);
    }

    protected Stream<String> streamFieldNames(Collection<DatabaseFieldMetadata> fields) {
        return fields.stream().map(DatabaseFieldMetadata::getName);
    }

    public Collection<String> getFieldNames(Collection<DatabaseFieldMetadata> fields) {
        return streamFieldNames(fields).collect(Collectors.toList());
    }

    public String getFieldNames(Collection<DatabaseFieldMetadata> fields, String delimiter) {
        return streamFieldNames(fields).collect(Collectors.joining(delimiter));
    }

    public String getFieldNames(Collection<DatabaseFieldMetadata> fields, String format, String delimiter) {
        return streamFieldNames(fields).map(name -> String.format(format, name)).collect(Collectors.joining(delimiter));
    }

    public String getFieldsPlaceholder(Collection<DatabaseFieldMetadata> fields, String delimiter) {
        return getFieldNames(fields, "?", delimiter);
    }

    public String getFieldsEqualPlaceholders(Collection<DatabaseFieldMetadata> fields, String delimiter) {
        return getFieldNames(fields, "%s=?", delimiter);
    }

    public DatabaseFieldMetadata getFieldByName(String name) {
        return nameToFieldMap.get(name);
    }

    public int setStatementFieldValues(Object e, PreparedStatement statement, Collection<DatabaseFieldMetadata> fields, int i)
            throws DatabaseError, SQLException {
        for (DatabaseFieldMetadata field : fields) {
            statement.setObject(i, field.getValue(e));
            i++;
        }

        return i;
    }

    public int setStatementFieldValues(Object e, PreparedStatement statement, Collection<DatabaseFieldMetadata> fields)
            throws DatabaseError, SQLException {
        return setStatementFieldValues(e, statement, fields, 1);
    }
}
