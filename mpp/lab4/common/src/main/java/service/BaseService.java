package service;

import domain.Score;

import java.util.ArrayList;
import java.util.List;

public abstract class BaseService implements IService {
    final List<IServiceObserver> observers = new ArrayList<>();

    void observerSetScore(Score score) {observers.forEach(observer -> observer.onSetScore(score));}

    public void addObserver(IServiceObserver observer) {
        observers.add(observer);
    }

    public void removeObserver(IServiceObserver observer) {
        observers.remove(observer);
    }
}
