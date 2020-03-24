package utils;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class ConfigManager {
    private final Properties properties = new Properties();

    public ConfigManager() {
        try (InputStream inputStream = ConfigManager.class.getResourceAsStream("/config.properties")) {
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
}
