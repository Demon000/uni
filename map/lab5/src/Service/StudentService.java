package Service;

import Domain.Student;
import Repository.BaseRepository;
import Validator.BaseEntityStringValidator;
import Validator.ValidationException;

public class StudentService extends BaseService<String, Student,
        BaseEntityStringValidator<Student>, BaseRepository<String, Student, BaseEntityStringValidator<Student>>> {
    public StudentService(BaseRepository repository, BaseEntityStringValidator<Student> validator) {
        super(repository, validator);
    }

    /**
     * Create a new student and save it.
     * @param id the id of the student
     * @param firstName the first name of the student
     * @param lastName the last name of the student
     * @param email the email of the student
     * @return the newly created student
     * @throws StudentServiceException if the student already exists
     * @throws ValidationException if the student is invalid
     */
    public Student create(String id, String firstName, String lastName, String email) throws StudentServiceException, ValidationException {
        if (repository.findOne(id) != null) {
            throw new StudentServiceException("Student already exists.");
        }

        Student student = new Student(id, firstName, lastName, email);
        repository.save(student);

        return student;
    }

    /**
     * Update an already created student.
     * @param id the id of the student
     * @param firstName the first name of the student
     * @param lastName the last name of the student
     * @param email the email of the student
     * @return the updated student
     * @throws StudentServiceException if the student does not exist
     * @throws ValidationException if the student is invalid
     */
    public Student update(String id, String firstName, String lastName, String email) throws StudentServiceException, ValidationException {
        if (repository.findOne(id) != null) {
            throw new StudentServiceException("Student does not exist.");
        }

        Student student = new Student(id, firstName, lastName, email);
        repository.update(student);

        return student;
    }
}
