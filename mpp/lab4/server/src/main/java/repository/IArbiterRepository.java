package repository;

import domain.Arbiter;

public interface IArbiterRepository {
    void add(Arbiter arbiter) throws RepositoryError;
    Arbiter findByNameAndPassword(String name, String password) throws RepositoryError;
}
