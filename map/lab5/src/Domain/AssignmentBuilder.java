package Domain;

import org.w3c.dom.Element;

public class AssignmentBuilder implements IBuilder<String, Assignment> {
    @Override
    public Assignment buildFromXML(Element element) {
        return Assignment.createFromXMLElement(element);
    }
}
