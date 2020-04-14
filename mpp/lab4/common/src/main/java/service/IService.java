package service;

import domain.Arbiter;
import domain.Score;
import domain.ScoreType;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface IService extends Remote {
    Arbiter loginArbiter(String name, String password) throws ServiceError, RemoteException;
    List<Score> getScores() throws ServiceError, RemoteException;
    List<Score> getScoresForType(ScoreType type) throws ServiceError, RemoteException;
    Score setScoreValue(int participantId, ScoreType type, int value) throws ServiceError, RemoteException;
    void addObserver(IServiceObserver observer) throws RemoteException;
    void removeObserver(IServiceObserver observer) throws RemoteException;
}
