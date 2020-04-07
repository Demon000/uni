using System.Xml.Linq;

namespace lab1
{
    public static class XmlUtils
    {
        public static string GetAttributeValue(this XElement element, string attributeName)
        {
            return element.Attribute(attributeName)?.Value;
        }
    }
}