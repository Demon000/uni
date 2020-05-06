package repository;

import domain.Arbiter;

import java.util.List;

public interface IArbiterRepository {
    void add(Arbiter arbiter) throws RepositoryError;
    Arbiter findById(int id) throws RepositoryError;
    List<Arbiter> find() throws RepositoryError;
}
