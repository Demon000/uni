package repository;

import domain.BaseEntity;

public interface IRepository<ID, E extends BaseEntity<ID>> {
    E find(ID id);
    Iterable<E> find();
    E add(E entity);
    E update(E entity);
    E remove(ID id);
    void empty();
}