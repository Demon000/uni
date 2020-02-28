package repository;

import domain.BaseEntity;

import java.util.HashMap;
import java.util.Map;

public class BaseRepository<ID, E extends BaseEntity<ID>> implements IRepository<ID, E> {
    protected Map<ID, E> entities = new HashMap<>();

    @Override
    public E find(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("Id cannot be null");
        }

        return entities.get(id);
    }

    @Override
    public Iterable<E> find() {
        return entities.values();
    }

    @Override
    public E add(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        return entities.put(entity.getId(), entity);
    }

    @Override
    public E update(E entity) {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            return null;
        } else {
            return entity;
        }
    }

    @Override
    public E remove(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("Id cannot be null");
        }

        return entities.remove(id);
    }

    @Override
    public void empty() {
        entities = new HashMap<>();
    }
}
