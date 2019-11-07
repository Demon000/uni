package Service;

import Domain.BaseEntity;
import Repository.BaseRepository;
import Validator.IValidator;

public class BaseService<ID, E extends BaseEntity<ID>, V extends IValidator<E>, R extends BaseRepository<ID, E, V>> {
    protected R repository;
    protected V validator;

    public BaseService(R repository, V validator) {
        this.repository = repository;
        this.validator = validator;
    }

    public E findOne(ID id) {
        return repository.findOne(id);
    }

    public Iterable<E> findAll() {
        return repository.findAll();
    }

    public E delete(ID id) {
        return repository.delete(id);
    }
}
