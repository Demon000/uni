package service;

import domain.Score;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IServiceObserver extends Remote {
    void onSetScore(Score score) throws ServiceError, RemoteException;
}
