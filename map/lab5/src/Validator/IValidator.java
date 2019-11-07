package Validator;

public interface IValidator<E> {
    void validate(E entity) throws ValidationException;
}