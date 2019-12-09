package validator;

import domain.Student;

import java.util.List;

public class StudentValidator extends BaseStringEntityValidator<Student> {
    /**
     * Validate a name.
     * @param name the name to be validated
     * @throws ValidationException if the name isn't valid
     */
    public void validateName(String name) throws ValidationException {
        if (name == null) {
            throw new ValidationException("Student name must not be null");
        }

        if (name.length() < 3) {
            throw new ValidationException("Student name must be at least 3 characters long");
        }

        String nameRegex = "[A-Z][a-z]+";
        if (!name.matches(nameRegex)) {
            throw new ValidationException("Student name must start with an uppercase letter " +
                    "followed by multiple lowercase letters");
        }
    }

    /**
     * Validate an email.
     * @param email the email to be validated
     * @throws ValidationException if the email isn't valid
     */
    public void validateEmail(String email) throws ValidationException {
        if (email == null) {
            throw new ValidationException("Student email must not be null");
        }

        String emailRegex = "[a-z]{4}[1-9]{4}@scs.ubbcluj.ro";
        if (!email.matches(emailRegex)) {
            throw new ValidationException(("Student email must be of format abcd1234@scs.ubbcluj.ro"));
        }
    }

    /**
     * Validate motivated weeks list.
     * @param motivatedWeeks the list of motivated weeks to validate
     * @throws ValidationException if the weeks contained in the given list are invalid
     */
    public void validateMotivatedWeeks(List<Long> motivatedWeeks) throws ValidationException {
        if (motivatedWeeks == null) {
            throw new ValidationException("Student motivated weeks must not be null");
        }

        for (Long w : motivatedWeeks) {
            long week = w;
            if (week < 1) {
                throw new ValidationException("Student motivated week must be at least 1");
            }

            if (week  > 14) {
                throw new ValidationException("Student motivated week must be at most 14");
            }
        }
    }

    /**
     * Validate a group.
     * @param group the group name to be validate
     * @throws ValidationException if the group name isn't valid
     */
    public void validateGroup(String group) throws ValidationException {
        if (group == null) {
            throw new ValidationException("Student group must not be null");
        }

        String groupRegex = "22[1-7]";
        if (!group.matches(groupRegex)) {
            throw new ValidationException("Student group must be of format 227");
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
    public void validate(Student student) throws ValidationException {
        super.validate(student);

        validateName(student.getFirstName());
        validateName(student.getLastName());
        validateEmail(student.getEmail());
        validateGroup(student.getGroup());
        validateProfessorName(student.getProfessorName());
        validateMotivatedWeeks(student.getMotivatedWeeks());
    }
}
