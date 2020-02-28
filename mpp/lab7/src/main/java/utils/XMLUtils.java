package utils;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.util.ArrayList;
import java.util.List;

public class XMLUtils {
    public static void appendChildValue(Element parentElement, String tagName, String value) {
        Document document = parentElement.getOwnerDocument();
        Element childElement = document.createElement(tagName);
        childElement.appendChild(document.createTextNode(value));
        parentElement.appendChild(childElement);
    }

    public static void appendListChildValues(Element parentElement, String tagName, String childTagName, List<String> list) {
        Document document = parentElement.getOwnerDocument();
        Element listElement = document.createElement(tagName);
        for (String value : list) {
            Element childElement = document.createElement(childTagName);
            childElement.appendChild(document.createTextNode(value));
            listElement.appendChild(childElement);
        }
        parentElement.appendChild(listElement);
    }

    public static List<Element> getChildren(Element parentElement) {
        List<Element> childElements = new ArrayList<>();
        NodeList childNodes = parentElement.getChildNodes();
        for (int i = 0; i < childNodes.getLength(); i++) {
            Node childNode = childNodes.item(i);
            if (childNode.getNodeType() == Node.ELEMENT_NODE) {
                Element childElement = (Element) childNode;
                childElements.add(childElement);
            }
        }

        return childElements;
    }

    public static List<Element> getChildrenForTagName(Element parentElement, String tagName) {
        List<Element> childElements = getChildren(parentElement);
        List<Element> childElementsForTag = new ArrayList<>();

        for (Element childElement : childElements) {
            if (childElement.getTagName().equals(tagName)) {
                childElementsForTag.add(childElement);
            }
        }

        return childElementsForTag;
    }

    public static Element getChildForTagName(Element parentElement, String tagName) {
        List<Element> childElements = getChildrenForTagName(parentElement, tagName);

        if (childElements.size() < 1) {
            return null;
        }

        return childElements.get(0);
    }

    public static String getChildValue(Element parentElement, String tagName) {
        Element childElement = getChildForTagName(parentElement, tagName);
        if (childElement == null) {
            return "";
        }

        return childElement.getTextContent();
    }

    public static List<String> getListChildrenValues(Element parentElement, String tagName, String childTagName) {
        Element listElement = getChildForTagName(parentElement, tagName);
        List<Element> childrenElements = getChildrenForTagName(listElement, childTagName);
        List<String> list = new ArrayList<>();

        for (Element childElement : childrenElements) {
            list.add(childElement.getTextContent());
        }

        return list;
    }
}
