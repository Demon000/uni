package Domain;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import java.util.Objects;

public class BaseEntity<ID> {
    public String TAG_NAME = "baseEntity";
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

    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }

    public Element toXMLElement(Document document) {
        return null;
    }

    public void setFromXMLElement(Element element) {
    }
}
