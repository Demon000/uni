package observer;

public interface Observer {
    void onChange(String key, Object oldValue, Object newValue);
}
