package observer;

import java.util.ArrayList;
import java.util.List;

public class Observable {
    final List<Observer> observers = new ArrayList<>();

    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    protected void change(String key, Object oldValue, Object newValue) {
        observers.forEach(observer -> observer.onChange(key, oldValue, newValue));
    }
}
