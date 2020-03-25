package service;

import domain.Arbiter;
import domain.Participant;
import domain.Score;
import domain.ScoreType;
import observer.Observable;
import repository.IArbiterRepository;
import repository.IParticipantRepository;
import repository.IScoreRepository;
import repository.RepositoryError;

import java.util.List;

public class Service extends Observable {
    public static final String SCORE_SET_CHANGE = "score_set_change";

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

    public void setScore(Score score, Arbiter arbiter) throws RepositoryError {
        scoreRepository.setScore(score.getParticipant().getId(), arbiter.getType(), score.getScore(arbiter.getType()));
        change(SCORE_SET_CHANGE, null, score);
    }

    public List<Score> getScoresForType(ScoreType type) throws RepositoryError {
        return scoreRepository.findScoresForTypeSortedDescending(type);
    }

    public List<Score> getScores() throws RepositoryError {
        return scoreRepository.findScoresSortedByName();
    }
}
