package Repository;

import Domain.Student;
import Validator.StudentValidator;

public class StudentRepository extends BaseRepository<String, Student, StudentValidator> {
    public StudentRepository(StudentValidator validator) {
        super(validator);
    }
}
