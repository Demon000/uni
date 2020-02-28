package validator;

public interface IValidator<E> {
    void validate(E entity) throws ValidationException;
}