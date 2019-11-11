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
            throw new ValidationException("Grade value is smaller than 0.");
        }

        if (value > 10) {
            throw new ValidationException("Grade value is bigger than 10.");
        }
    }

    /**
     * Validate a penalty.
     * @param penalty the penalty to validate
     * @throws ValidationException if the penalty is invalid
     */
    public void validatePenalty(long penalty) throws ValidationException {
        if (penalty < 0) {
            throw new ValidationException("Grade penalty is negative.");
        }

        if (penalty > 2) {
            throw new ValidationException("Grade penalty is bigger than 2.");
        }
    }

    @Override
    public void validate(Grade grade) throws ValidationException {
        validateValue(grade.getValue());
        validatePenalty(grade.getPenalty());
    }
}
