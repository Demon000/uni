package service;

import domain.Arbiter;
import domain.Score;
import domain.ScoreType;
import repository.IArbiterRepository;
import repository.IParticipantRepository;
import repository.IScoreRepository;
import repository.RepositoryError;
import utils.ServiceError;

import java.util.List;

public class Service extends BaseService {
    private final IParticipantRepository participantRepository;
    private final IArbiterRepository arbiterRepository;
    private final IScoreRepository scoreRepository;

    public Service(IParticipantRepository participantRepository, IArbiterRepository arbiterRepository, IScoreRepository scoreRepository) {
        this.participantRepository = participantRepository;
        this.arbiterRepository = arbiterRepository;
        this.scoreRepository = scoreRepository;
    }

    public Arbiter loginArbiter(String name, String password) throws ServiceError {
        try {
            return arbiterRepository.findByNameAndPassword(name, password);
        } catch (RepositoryError e) {
            throw new ServiceError(e);
        }
    }

    public Score setScoreValue(int participantId, ScoreType type, int value) throws ServiceError {
        try {
            scoreRepository.setScore(participantId, type, value);
            Score score = scoreRepository.getScore(participantId);
            observerSetScore(score);
            return score;
        } catch (RepositoryError e) {
            throw new ServiceError(e);
        }
    }

    public List<Score> getScoresForType(ScoreType type) throws ServiceError {
        try {
            return scoreRepository.findScoresForTypeSortedDescending(type);
        } catch (RepositoryError e) {
            throw new ServiceError(e);
        }
    }

    public List<Score> getScores() throws ServiceError {
        try {
            return scoreRepository.findScoresSortedByName();
        } catch (RepositoryError e) {
            throw new ServiceError(e);
        }
    }
}
