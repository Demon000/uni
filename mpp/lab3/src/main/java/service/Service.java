package service;

import domain.Arbiter;
import domain.Participant;
import domain.ParticipantScore;
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

    public void setScore(Participant participant, Arbiter arbiter, int score) throws RepositoryError {
        scoreRepository.setScore(participant.getId(), arbiter.getId(), score);
    }

    public List<ParticipantScore> getScoresForType(ScoreType type) throws RepositoryError {
        return scoreRepository.findScoresForTypeSortedDescending(type);
    }

    public List<ParticipantScore> getScores() throws RepositoryError {
        return scoreRepository.findScoresSortedByName();
    }
}
