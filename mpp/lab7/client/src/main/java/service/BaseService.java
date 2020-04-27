package service;

import domain.Score;

import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;

public abstract class BaseService implements IService {
    protected final List<IServiceObserver> observers = new ArrayList<>();

    void observerSetScore(Score score) {
        observers.forEach(observer -> observer.onSetScore(score));
    }

    void observersConnectionStatusChange(ServiceConnectionStatus status) {
        observers.forEach(observer -> observer.onConnectionStatusChange(status));
    }

    public void addObserver(IServiceObserver observer) {
        observers.add(observer);
        if (observers.size() == 1) {
            onAddFirstObserver(observer);
        }
    }

    public void removeObserver(IServiceObserver observer) {
        observers.remove(observer);
        if (observers.size() == 0) {
            onRemoveLastObserver(observer);
        }
    }

    public abstract void onAddFirstObserver(IServiceObserver observer);

    public abstract void onRemoveLastObserver(IServiceObserver observer);
}
