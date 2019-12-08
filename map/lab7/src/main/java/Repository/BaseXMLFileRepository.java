package Repository;

import Domain.BaseEntity;
import Domain.IBuilder;
import Validator.IValidator;
import Validator.ValidationException;
import org.w3c.dom.*;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static Utils.XMLUtils.getChildren;

public class BaseXMLFileRepository<ID, E extends BaseEntity<ID>, B extends IBuilder<ID, E>, V extends IValidator<E>>
        extends BaseRepository<ID, E, V> implements IRepository<ID, E> {
    private B builder;
    private String filePath;

    public BaseXMLFileRepository(String filePath, V validator, B builder) {
        super(validator);

        this.filePath = filePath;
        this.builder = builder;
    }

    private Map<ID, E> readFromFile() {
        Map<ID, E> entities = new HashMap<>();
        File file = new File(filePath);

        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder documentBuilder;
        try {
            documentBuilder = documentBuilderFactory.newDocumentBuilder();
        } catch (ParserConfigurationException e) {
            //e.printStackTrace();
            return entities;
        }

        Document document;
        try {
            document = documentBuilder.parse(file);
        } catch (Exception e) {
            //e.printStackTrace();
            return entities;
        }

        Element root = document.getDocumentElement();
        root.normalize();

        List<Element> elements = getChildren(root);
        for (Element element : elements) {
            E entity = builder.buildFromXML(element);
            entities.put(entity.getId(), entity);
        }

        return entities;
    }

    private void writeToFile(Map<ID, E> entities) {
        DocumentBuilderFactory documentBuilderFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder documentBuilder;
        try {
            documentBuilder = documentBuilderFactory.newDocumentBuilder();
        } catch (ParserConfigurationException e) {
            //e.printStackTrace();
            return;
        }

        Document document = documentBuilder.newDocument();
        Element root = document.createElement("root");

        for (E entity : entities.values()) {
            Element element = entity.toXMLElement(document);
            root.appendChild(element);
        }

        TransformerFactory transFactory = TransformerFactory.newInstance();
        Transformer transformer;
        try {
            transformer = transFactory.newTransformer();
        } catch (TransformerException e) {
            //e.printStackTrace();
            return;
        }

        DOMSource domSource = new DOMSource(root);
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
        StreamResult streamResult = new StreamResult(new File(filePath));
        //StreamResult streamResult = new StreamResult(System.out);

        try {
            transformer.transform(domSource, streamResult);
        } catch (TransformerException e) {
            //e.printStackTrace();
        }
    }

    @Override
    public E findOne(ID id) {
        entities = readFromFile();
        return super.findOne(id);
    }

    @Override
    public Iterable<E> findAll() {
        entities = readFromFile();
        return super.findAll();
    }

    @Override
    public E save(E entity) throws ValidationException {
        entities = readFromFile();
        E result = super.save(entity);
        writeToFile(entities);
        return result;
    }

    @Override
    public E delete(ID id) {
        entities = readFromFile();
        E result = super.delete(id);
        writeToFile(entities);
        return result;
    }

    @Override
    public E update(E entity) throws ValidationException {
        entities = readFromFile();
        E result = super.update(entity);
        writeToFile(entities);
        return result;
    }
}
