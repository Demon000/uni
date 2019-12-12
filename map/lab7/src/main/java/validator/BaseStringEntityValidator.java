package validator;

import domain.BaseEntity;

public abstract class BaseStringEntityValidator<E extends BaseEntity<String>> implements IValidator<E> {
    public abstract void validateId(String id) throws ValidationException;

    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    public void validateSimpleId(String id) throws ValidationException {
        String idRegex = "[0-9]+";
        ValidationException exception = new ValidationException();
        exception.addExceptionIf(() -> !id.matches(idRegex),
                new ValidationException("Id must be formed of digits only"));
        exception.throwIfNotEmpty();
    }

    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    public void validateComplexId(String id) throws ValidationException {
        String idRegex = "([0-9]+)(\\+[1-9]+)?";
        ValidationException exception = new ValidationException();
        exception.addExceptionIf(() -> !id.matches(idRegex),
                new ValidationException("Id must be formed of digits only"));
        exception.throwIfNotEmpty();
    }

    @Override
    public void validate(E entity) throws ValidationException {
        ValidationException exception = new ValidationException();
        exception.addExceptionIfThrown(() -> validateId(entity.getId()));
        exception.throwIfNotEmpty();
    }
}
