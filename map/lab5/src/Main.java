import Domain.Assignment;
import Repository.AssignmentRepository;
import Repository.GradeRepository;
import Repository.StudentRepository;
import Service.CommonService;
import Tests.Tests;
import Time.DateIntervalError;
import Time.UniversitySemester;
import Time.UniversitySemesterError;
import Time.UniversityYear;
import UserInterface.Console;
import Validator.AssignmentValidator;
import Validator.GradeValidator;
import Validator.StudentValidator;

import java.time.LocalDate;
import java.util.ConcurrentModificationException;

public class Main {
    private static UniversityYear createUniversityYear() throws UniversitySemesterError, DateIntervalError {
        UniversitySemester firstSemester;
        UniversitySemester secondSemester;

        firstSemester = UniversitySemester.fromLocalDates(
                LocalDate.of(2019, 9, 30), LocalDate.of(2019, 12, 20),
                LocalDate.of(2020, 1, 6), LocalDate.of(2020, 1, 17)
        );

        secondSemester = UniversitySemester.fromLocalDates(
                LocalDate.of(2020, 2, 24), LocalDate.of(2020, 4, 17),
                LocalDate.of(2020, 4, 27), LocalDate.of(2020, 6, 5)
        );

        return new UniversityYear(firstSemester, secondSemester);
    }

    public static void main(String[] args) {
        Tests tests = new Tests();
        tests.testAll();

        UniversityYear year;

        try {
            year = createUniversityYear();
        } catch (UniversitySemesterError | DateIntervalError e) {
            System.out.println(e);
            return;
        }

        StudentValidator studentValidator = new StudentValidator();
        StudentRepository studentRepository = new StudentRepository(studentValidator);

        AssignmentValidator assignmentValidator = new AssignmentValidator(year);
        AssignmentRepository assignmentRepository = new AssignmentRepository(assignmentValidator);

        GradeValidator gradeValidator = new GradeValidator();
        GradeRepository gradeRepository = new GradeRepository(gradeValidator);

        CommonService service = new CommonService(studentRepository, assignmentRepository, gradeRepository, year);
        Console console = new Console(service);

        console.run();
    }
}
