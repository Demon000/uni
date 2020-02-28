package validator;

import domain.Student;

import java.util.List;

public class StudentValidator extends BaseStringEntityValidator<Student> {
    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    @Override
    public void validateId(String id) throws ValidationException {
        validateSimpleId(id);
    }

    /**
     * Validate a name.
     * @param name the name to be validated
     * @throws ValidationException if the name isn't valid
     */
    public void validateName(String name) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> name == null,
                new ValidationException("Student name must not be null"));
        exception.throwIfNotEmpty();

        exception.addExceptionIf(() -> name.length() < 3,
                new ValidationException("Student name must be at least 3 characters long"));

        String nameRegex = "[A-Z][a-z]+";
        exception.addExceptionIf(() -> !name.matches(nameRegex),
                new ValidationException("Student name must start with an uppercase letter " +
                        "followed by multiple lowercase letters"));

        exception.throwIfNotEmpty();
    }

    /**
     * Validate an email.
     * @param email the email to be validated
     * @throws ValidationException if the email isn't valid
     */
    public void validateEmail(String email) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> email == null,
                new ValidationException("Student email must not be null"));
        exception.throwIfNotEmpty();

        String emailRegex = "[a-z]{4}[1-9]{4}@scs.ubbcluj.ro";
        exception.addExceptionIf(() -> !email.matches(emailRegex),
                new ValidationException("Student email must be of format abcd1234@scs.ubbcluj.ro"));
        
        exception.throwIfNotEmpty();
    }

    /**
     * Validate motivated weeks list.
     * @param motivatedWeeks the list of motivated weeks to validate
     * @throws ValidationException if the weeks contained in the given list are invalid
     */
    public void validateMotivatedWeeks(List<Long> motivatedWeeks) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> motivatedWeeks == null,
                new ValidationException("Student motivated weeks must not be null"));
        exception.throwIfNotEmpty();

        for (Long w : motivatedWeeks) {
            long week = w;
            exception.addExceptionIf(() -> week < 1,
                    new ValidationException("Student motivated week must be at least 1"));

            exception.addExceptionIf(() -> week > 14,
                    new ValidationException("Student motivated week must be at most 14"));
        }

        exception.throwIfNotEmpty();
    }

    /**
     * Validate a group.
     * @param group the group name to be validate
     * @throws ValidationException if the group name isn't valid
     */
    public void validateGroup(String group) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> group == null,
                new ValidationException("Student group must not be null"));
        exception.throwIfNotEmpty();

        String groupRegex = "22[1-7]";
        exception.addExceptionIf(() -> !group.matches(groupRegex),
                new ValidationException("Student group must be of format 227"));

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
    public void validate(Student student) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> student == null,
                new ValidationException("Student must not be null"));
        exception.throwIfNotEmpty();

        exception.addExceptionIfThrown(() -> super.validate(student));
        exception.addExceptionIfThrown(() -> validateName(student.getFirstName()));
        exception.addExceptionIfThrown(() -> validateName(student.getLastName()));
        exception.addExceptionIfThrown(() -> validateEmail(student.getEmail()));
        exception.addExceptionIfThrown(() -> validateGroup(student.getGroup()));
        exception.addExceptionIfThrown(() -> validateProfessorName(student.getProfessorName()));
        exception.addExceptionIfThrown(() -> validateMotivatedWeeks(student.getMotivatedWeeks()));

        exception.throwIfNotEmpty();
    }
}
