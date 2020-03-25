package repository;

import domain.Score;
import domain.ScoreType;

import java.util.List;

public interface IScoreRepository {
    void addScore(int participantId, ScoreType type, int score) throws RepositoryError;
    void updateScore(int participantId, ScoreType type, int score) throws RepositoryError;
    void setScore(int participantId, ScoreType type, int score) throws RepositoryError;
    List<Score> findScoresForTypeSortedDescending(ScoreType type) throws RepositoryError;
    List<Score> findScoresSortedByName() throws RepositoryError;
}
