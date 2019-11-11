package Validator;

import Domain.Grade;

public class GradeValidator extends BaseEntityStringValidator<Grade> {
    /**
     * Validate a grade value.
     * @param value the value to validate
     * @throws ValidationException if the value is invalid
     */
    public void validateValue(int value) throws ValidationException {
        if (value < 1) {
            throw new ValidationException("Grade must be at least 0");
        }

        if (value > 10) {
            throw new ValidationException("Grade must be at most 10");
        }
    }

    /**
     * Validate a penalty.
     * @param penalty the penalty to validate
     * @throws ValidationException if the penalty is invalid
     */
    public void validatePenalty(long penalty) throws ValidationException {
        if (penalty < 0) {
            throw new ValidationException("Grade penalty must be at least 0");
        }

        if (penalty > 2) {
            throw new ValidationException("Grade penalty must be at most 2");
        }
    }

    @Override
    public void validate(Grade grade) throws ValidationException {
        validateValue(grade.getValue());
        validatePenalty(grade.getPenalty());
    }
}
