package validator;

import domain.Grade;

public class GradeValidator extends BaseStringEntityValidator<Grade> {
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

    /**
     * Validate a professor name.
     * @param professorName the name to be validated
     * @throws ValidationException if the name isn't valid
     */
    public void validateProfessorName(String professorName) throws ValidationException {
        if (professorName == null) {
            throw new ValidationException("Professor name must not be null");
        }

        if (professorName.length() < 3) {
            throw new ValidationException("Professor name must be at least 3 characters long");
        }
    }

    @Override
    public void validate(Grade grade) throws ValidationException {
        validateValue(grade.getValue());
        validatePenalty(grade.getPenalty());
        validateProfessorName(grade.getProfessorName());
    }
}
