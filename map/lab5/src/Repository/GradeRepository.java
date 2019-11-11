package Repository;

import Domain.Grade;
import Validator.GradeValidator;

public class GradeRepository extends BaseRepository<String, Grade, GradeValidator> {
    public GradeRepository(GradeValidator validator) {
        super(validator);
    }
}
