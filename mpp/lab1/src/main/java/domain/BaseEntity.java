package domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.util.Objects;

@DatabaseTableName("BaseEntity")
public abstract class BaseEntity<ID> {
    @DatabasePrimaryKey("Id", "integer")
    private ID id;

    public ID getId() {
        return id;
    }

    public void setId(ID id) {
        this.id = id;
    }

    @Override
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        }

        if (this.getClass() != other.getClass()) {
            return false;
        }

        BaseEntity<?> otherEntity = (BaseEntity<?>) other;

        return getId() == otherEntity.getId();
    }

    public abstract boolean matches(String input);

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }

    public abstract  Element toXMLElement(Document document);
}
