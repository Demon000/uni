package Validator;

import Domain.BaseEntity;

public class BaseStringEntityValidator<E extends BaseEntity<String>> implements IValidator<E> {
    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    public void validateId(String id) throws ValidationException {
        String idRegex = "([1-9]+)(\\+[1-9]+)?";
        if (!id.matches(idRegex)) {
            throw new ValidationException("Id must be formed of digits only");
        }
    }

    @Override
    public void validate(E entity) throws ValidationException {
        validateId(entity.getId());
    }
}
