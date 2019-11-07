package Validator;

import Domain.Student;

public class StudentValidator implements IValidator<Student> {
    private final String idRegex = "[1-9]+";
    private final String nameRegex = "[A-Z][a-z -]+";
    private final String emailRegex = "[a-z]{4}[1-9]{4}@scs.ubbcluj.ro";

    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    public void validateId(String id) throws ValidationException {
        if (!id.matches(idRegex)) {
            throw new ValidationException("Given string doesn't look like an id");
        }
    }

    /**
     * Validate a name.
     * @param name the name to be validated
     * @throws ValidationException if the name isn't valid
     */
    public void validateName(String name) throws ValidationException {
        if (name.length() < 3) {
            throw new ValidationException("Given string is too short for a name");
        }

        if (!name.matches(nameRegex)) {
            throw new ValidationException("Given string doesn't look like a name");
        }
    }

    /**
     * Validate an email.
     * @param email the email to be validated
     * @throws ValidationException if the email isn't valid
     */
    public void validateEmail(String email) throws ValidationException {
        if (!email.matches(emailRegex)) {
            throw new ValidationException(("Given string isn't a valid email address."));
        }
    }

    @Override
    public void validate(Student student) throws ValidationException {
        validateId(student.getId());
        validateName(student.getFirstName());
        validateName(student.getLastName());
        validateEmail(student.getEmail());
    }
}
