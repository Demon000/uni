package utils;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class Configuration {
    private final Properties properties = new Properties();

    public Configuration(Class<?> clazz) {
        try (InputStream inputStream = clazz.getResourceAsStream("/config.properties")) {
            properties.load(inputStream);
        } catch (IOException e) {
            e.printStackTrace(System.out);
        }
    }

    public String getValue(String name) {
        return properties.getProperty(name);
    }

    public String getValue(String name, String value) {
        return properties.getProperty(name, value);
    }

    public int getIntegerValue(String name, int value) {
        return Integer.parseInt(properties.getProperty(name, Integer.toString(value)));
    }
}
