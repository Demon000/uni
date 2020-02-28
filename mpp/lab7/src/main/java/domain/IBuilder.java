package domain;

import org.w3c.dom.Element;

public interface IBuilder<ID, E extends BaseEntity<ID>> {
    E buildFromXML(Element element);
}
