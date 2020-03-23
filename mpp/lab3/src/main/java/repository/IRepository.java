package repository;

import java.util.List;

public interface IRepository<E> {
    void add(E e) throws RepositoryError;
    List<E> find() throws RepositoryError;
    E findById(E e) throws RepositoryError;
    void update(E e) throws RepositoryError;
    void delete(E e) throws RepositoryError;
}
