package repository;

import domain.ParticipantScore;
import domain.ScoreType;

import java.util.List;

public interface IScoreRepository {
    void addScore(int participantId, int arbiterId, int score) throws RepositoryError;
    void updateScore(int participantId, int arbiterId, int score) throws RepositoryError;
    void setScore(int participantId, int arbiterId, int score) throws RepositoryError;
    List<ParticipantScore> findScoresForTypeSortedDescending(ScoreType type) throws RepositoryError;
    List<ParticipantScore> findScoresSortedByName() throws RepositoryError;
}
