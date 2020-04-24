package repository;

import domain.BaseEntity;
import validator.IValidator;
import validator.ValidationException;

import java.util.HashMap;
import java.util.Map;

public class BaseRepository<ID, E extends BaseEntity<ID>, V extends IValidator<E>> implements IRepository<ID, E> {
    protected Map<ID, E> entities = new HashMap<>();
    private final V validator;

    public BaseRepository(V validator) {
        this.validator = validator;
    }

    @Override
    public E findOne(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("Id cannot be null");
        }

        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) throws ValidationException {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        validator.validate(entity);

        return entities.put(entity.getId(), entity);
    }

    @Override
    public E delete(ID id) {
        if (id == null) {
            throw new IllegalArgumentException("Id cannot be null");
        }

        return entities.remove(id);
    }

    @Override
    public E update(E entity) throws ValidationException {
        if (entity == null) {
            throw new IllegalArgumentException("Entity cannot be null");
        }

        validator.validate(entity);

        if (entities.get(entity.getId()) != null) {
            entities.put(entity.getId(), entity);
            return null;
        } else {
            return entity;
        }
    }
}
