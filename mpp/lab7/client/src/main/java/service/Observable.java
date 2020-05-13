package service;

import domain.Score;

import java.util.ArrayList;
import java.util.List;

public abstract class Observable implements IObservable {
    protected final List<IObserver> observers = new ArrayList<>();

    protected void observersSendEvent(String name, Object object) {
        observers.forEach(observer -> observer.onEvent(name, object));
    }

    public void addObserver(IObserver observer) {
        observers.add(observer);
        if (observers.size() == 1) {
            onAddFirstObserver(observer);
        }
    }

    public void removeObserver(IObserver observer) {
        observers.remove(observer);
        if (observers.size() == 0) {
            onRemoveLastObserver(observer);
        }
    }

    protected void onAddFirstObserver(IObserver observer) {}

    protected void onRemoveLastObserver(IObserver observer) {}
}
