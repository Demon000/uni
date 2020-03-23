package repository;

import java.lang.reflect.Field;
import java.util.StringJoiner;

public class DatabaseFieldMetadata {
    private final Field field;
    private final String name;
    private final String type;
    private final String foreignKey;
    private final boolean isPrimaryKey;
    private final boolean isNotNull;
    private final boolean isUnique;

    public DatabaseFieldMetadata(Field field) throws DatabaseError {
        this.field = field;

        DatabaseField df = field.getAnnotation(DatabaseField.class);
        if (df == null) {
            throw new DatabaseError("Failed to find DatabaseField annotation on generic parameter fields");
        }

        this.name = df.name();
        this.type = df.type();
        this.isPrimaryKey = df.primaryKey();
        this.isNotNull = df.notNull();
        this.isUnique = df.unique();
        this.foreignKey = df.foreignKey();
    }

    public String getName() {
        return name;
    }

    public String getType() {
        return type;
    }

    public boolean isPrimaryKey() {
        return isPrimaryKey;
    }

    public boolean isNotNull() {
        return isNotNull;
    }

    public boolean isUnique() {
        return isUnique;
    }

    public String getForeignKey() {
        return foreignKey;
    }

    public Field getField() {
        return field;
    }

    public String getForeignKeyConstraint() {
        StringJoiner joiner = new StringJoiner(" ");

        joiner.add("foreign key");
        joiner.add("(");
        joiner.add(name);
        joiner.add(")");
        joiner.add("references");
        joiner.add(foreignKey);
        joiner.add(")");

        return joiner.toString();
    }

    public String getFieldCreationString() {
        StringJoiner joiner = new StringJoiner(" ");
        joiner.add(name);
        joiner.add(type);
        if (isNotNull) {
            joiner.add("not null");
        }
        if (isUnique) {
            joiner.add("unique");
        }

        return joiner.toString();
    }

    public Object getValue(Object object) throws DatabaseError {
        try {
            field.setAccessible(true);
            return field.get(object);
        } catch (IllegalAccessException e) {
            throw new DatabaseError(String.format("Failed to get %s", name));
        }
    }

    public void setValue(Object object, Object value) throws DatabaseError {
        try {
            field.setAccessible(true);

            field.set(object, value);
        } catch (IllegalAccessException e) {
            throw new DatabaseError(String.format("Failed to set %s value", name));
        }
    }
}
