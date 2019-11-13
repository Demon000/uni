package Validator;

import Domain.Student;

public class StudentValidator extends BaseEntityStringValidator<Student> {

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
            throw new ValidationException(("Student email must be of format abcd12@scs.ubbcluj.ro"));
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

    @Override
    public void validate(Student student) throws ValidationException {
        super.validate(student);

        validateName(student.getFirstName());
        validateName(student.getLastName());
        validateEmail(student.getEmail());
        validateGroup(student.getGroup());
    }
}
