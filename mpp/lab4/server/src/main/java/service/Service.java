package service;

import domain.Arbiter;
import domain.Score;
import domain.ScoreType;
import repository.IArbiterRepository;
import repository.IParticipantRepository;
import repository.IScoreRepository;
import repository.RepositoryError;

import java.util.List;

public class Service {
    private final IParticipantRepository participantRepository;
    private final IArbiterRepository arbiterRepository;
    private final IScoreRepository scoreRepository;

    public Service(IParticipantRepository participantRepository, IArbiterRepository arbiterRepository, IScoreRepository scoreRepository) {
        this.participantRepository = participantRepository;
        this.arbiterRepository = arbiterRepository;
        this.scoreRepository = scoreRepository;
    }

    public Arbiter loginArbiter(String name, String password) throws RepositoryError {
        return arbiterRepository.findByNameAndPassword(name, password);
    }

    public Score setScoreValue(int participantId, ScoreType type, int value) throws RepositoryError {
        scoreRepository.setScore(participantId, type, value);
        return scoreRepository.getScore(participantId);
    }

    public List<Score> getScoresForType(ScoreType type) throws RepositoryError {
        return scoreRepository.findScoresForTypeSortedDescending(type);
    }

    public List<Score> getScores() throws RepositoryError {
        return scoreRepository.findScoresSortedByName();
    }
}
