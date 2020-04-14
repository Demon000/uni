package service;

import domain.Arbiter;
import domain.Score;
import domain.ScoreType;
import utils.ServiceError;

import java.util.List;

public interface IService {
    Arbiter loginArbiter(String name, String password) throws ServiceError;
    List<Score> getScores() throws ServiceError;
    List<Score> getScoresForType(ScoreType type) throws ServiceError;
    Score setScoreValue(int participantId, ScoreType type, int value) throws ServiceError;
    void addObserver(IServiceObserver observer);
    void removeObserver(IServiceObserver observer);
}
