package domain;

import java.util.Objects;

public abstract class BaseEntity<ID> {
    private ID id;

    public BaseEntity(ID id) {
        this.id = id;
    }

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

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }
}
