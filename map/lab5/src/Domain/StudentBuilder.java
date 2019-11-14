package Domain;

import org.w3c.dom.Element;

public class StudentBuilder implements IBuilder<String, Student> {
    @Override
    public Student buildFromXML(Element element) {
        return Student.createFromXMLElement(element);
    }
}
