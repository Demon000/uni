package Repository;

import Domain.Assignment;
import Validator.AssignmentValidator;

public class AssignmentRepository extends BaseRepository<String, Assignment, AssignmentValidator> {
    public AssignmentRepository(AssignmentValidator validator) {
        super(validator);
    }
}
