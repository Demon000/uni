package Domain;

import org.w3c.dom.Element;

public class GradeBuilder implements IBuilder<String, Grade> {
    @Override
    public Grade buildFromXML(Element element) {
        return Grade.createFromXMLElement(element);
    }
}
