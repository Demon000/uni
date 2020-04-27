package service;

import domain.Arbiter;
import domain.Score;

import java.util.List;

public interface IService {
    Arbiter loginArbiter(String name, String password) throws ServiceError;
    List<Score> getScores() throws ServiceError;
    List<Score> getRankings() throws ServiceError;
    Score setScoreValue(int participantId, int value) throws ServiceError;
    void addObserver(IServiceObserver observer);
    void removeObserver(IServiceObserver observer);

    void start();
    void stop();
    ServiceConnectionStatus getConnectionStatus();
}
