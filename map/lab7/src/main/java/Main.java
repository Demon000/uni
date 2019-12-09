import controller.StudentsController;
import domain.*;
import repository.*;
import service.CommonService;
import time.DateIntervalError;
import time.UniversitySemester;
import time.UniversitySemesterError;
import time.UniversityYear;
import validator.AssignmentValidator;
import validator.GradeValidator;
import validator.StudentValidator;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.time.LocalDate;

public class Main extends Application {
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
        //Tests tests = new Tests();
        //tests.testAll();

        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        UniversityYear year;

        try {
            year = createUniversityYear();
        } catch (UniversitySemesterError | DateIntervalError e) {
            System.out.println(e);
            return;
        }

        StudentValidator studentValidator = new StudentValidator();
        //BaseRepository<String, Student, StudentValidator> studentRepository =
        //      new BaseRepository<>(studentValidator);
        Student.Builder studentBuilder = new Student.Builder();
        BaseRepository<String, Student, StudentValidator> studentRepository =
                new BaseXMLFileRepository<>("students.xml",
                        studentValidator, studentBuilder);

        AssignmentValidator assignmentValidator = new AssignmentValidator(year);
        //BaseRepository<String, Assignment, AssignmentValidator> assignmentRepository =
        //      new BaseRepository<>(assignmentValidator);
        Assignment.Builder assignmentBuilder = new Assignment.Builder();
        BaseRepository<String, Assignment, AssignmentValidator> assignmentRepository =
                new BaseXMLFileRepository<>("assignments.xml",
                        assignmentValidator, assignmentBuilder);


        GradeValidator gradeValidator = new GradeValidator();
        //BaseRepository<String, Grade, GradeValidator> gradeRepository =
        //      new BaseRepository<>(gradeValidator);
        Grade.Builder gradeBuilder = new Grade.Builder();
        BaseRepository<String, Grade, GradeValidator> gradeRepository
                = new BaseXMLFileRepository<>("grades.xml",
                gradeValidator, gradeBuilder);

        CommonService service = new CommonService(studentRepository, assignmentRepository, gradeRepository, year);

        StudentsController studentsController = new StudentsController(service);
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource(StudentsController.VIEW_NAME));
        loader.setController(studentsController);

        Scene scene = new Scene(loader.load());
        primaryStage.setScene(scene);
        primaryStage.setTitle(StudentsController.VIEW_TITLE);
        primaryStage.show();
    }
}
