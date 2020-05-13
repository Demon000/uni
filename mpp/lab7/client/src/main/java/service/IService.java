package service;

import domain.Arbiter;
import domain.Score;

import java.util.List;

public interface IService extends ICanStart, IObservable {
    Arbiter loginArbiter(String name, String password) throws ServiceError;
    void logout();
    Arbiter getLoggedInArbiter();

    List<Score> getScores() throws ServiceError;
    List<Score> getRankings() throws ServiceError;

    Score setScoreValue(int participantId, int value) throws ServiceError;
}
