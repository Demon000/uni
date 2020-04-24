package validator;

import domain.Grade;

public class GradeValidator extends BaseStringEntityValidator<Grade> {
    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    @Override
    public void validateId(String id) throws ValidationException {
        validateComplexId(id);
    }

    /**
     * Validate a grade value.
     * @param value the value to validate
     * @throws ValidationException if the value is invalid
     */
    public void validateValue(int value) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> value < 1,
                new ValidationException("Grade must be at least 0"));

        exception.addExceptionIf(() -> value > 10,
                new ValidationException("Grade must be at most 10"));

        exception.throwIfNotEmpty();
    }

    /**
     * Validate a penalty.
     * @param penalty the penalty to validate
     * @throws ValidationException if the penalty is invalid
     */
    public void validatePenalty(long penalty) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> penalty < 0,
                new ValidationException("Grade penalty must be at least 0"));

        exception.addExceptionIf(() -> penalty > 2,
                new ValidationException("Grade penalty must be at most 2"));

        exception.throwIfNotEmpty();
    }

    /**
     * Validate a professor name.
     * @param professorName the name to be validated
     * @throws ValidationException if the name isn't valid
     */
    public void validateProfessorName(String professorName) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> professorName == null,
                new ValidationException("Professor name must not be null"));
        exception.throwIfNotEmpty();

        exception.addExceptionIf(() -> professorName.length() < 3,
                new ValidationException("Professor name must be at least 3 characters long"));
        exception.throwIfNotEmpty();
    }

    @Override
    public void validate(Grade grade) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIfThrown(() -> super.validate(grade));
        exception.addExceptionIfThrown(() -> validateValue(grade.getValue()));
        exception.addExceptionIfThrown(() -> validatePenalty(grade.getPenalty()));
        exception.addExceptionIfThrown(() -> validateProfessorName(grade.getProfessorName()));

        exception.throwIfNotEmpty();
    }
}
