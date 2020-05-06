package repository;

import domain.Race;

import java.util.List;

public interface IRaceRepository {
    void add(Race race) throws RepositoryError;
    Race findById(int id) throws RepositoryError;
    List<Race> find() throws RepositoryError;
    void update(Race race) throws RepositoryError;
    void delete(Race race) throws RepositoryError;
}
