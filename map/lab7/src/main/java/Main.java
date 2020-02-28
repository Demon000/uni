import controller.AssignmentsController;
import controller.GradesController;
import controller.StudentsController;
import controller.WindowsController;
import domain.*;
import javafx.stage.Window;
import repository.*;
import service.CommonService;
import time.DateIntervalError;
import time.UniversitySemester;
import time.UniversitySemesterError;
import time.UniversityYear;
import ui.Console;
import validator.AssignmentValidator;
import validator.GradeValidator;
import validator.StudentValidator;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.time.LocalDate;

//public class Main extends Application {
public class Main {
    static UniversityYear year;
    static BaseRepository<String, Student, StudentValidator> studentRepository;
    static BaseRepository<String, Assignment, AssignmentValidator> assignmentRepository;
    static BaseRepository<String, Grade, GradeValidator> gradeRepository;
    static CommonService service;
    private static void createUniversityYear() throws UniversitySemesterError, DateIntervalError {
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

        year = new UniversityYear(firstSemester, secondSemester);
    }

    private static void createRepositories() {
        StudentValidator studentValidator = new StudentValidator();
        //studentRepository = new BaseRepository<>(studentValidator);
        Student.Builder studentBuilder = new Student.Builder();
        studentRepository = new BaseXMLFileRepository<>("students.xml",
                        studentValidator, studentBuilder);

        AssignmentValidator assignmentValidator = new AssignmentValidator(year);
        //assignmentRepository = new BaseRepository<>(assignmentValidator);
        Assignment.Builder assignmentBuilder = new Assignment.Builder();
        assignmentRepository = new BaseXMLFileRepository<>("assignments.xml",
                        assignmentValidator, assignmentBuilder);


        GradeValidator gradeValidator = new GradeValidator();
        //gradeRepository = new BaseRepository<>(gradeValidator);
        Grade.Builder gradeBuilder = new Grade.Builder();
        gradeRepository = new BaseXMLFileRepository<>("grades.xml",
                gradeValidator, gradeBuilder);
    }

    private static void createService() {
        service = new CommonService(studentRepository, assignmentRepository, gradeRepository, year);
    }

    private static void runConsole() {
        Console console = new Console(service);
        console.run();
    }

    public static void main(String[] args) {
        //Tests tests = new Tests();
        //tests.testAll();
        //launch(args);

        createRepositories();
        createService();
        runConsole();
    }

//    @Override
//    public void start(Stage primaryStage) throws Exception {
//        WindowsController windowsController = new WindowsController(service, year);
//        FXMLLoader loader = new FXMLLoader();
//        loader.setLocation(getClass().getResource(WindowsController.VIEW_NAME));
//        loader.setController(windowsController);
//
//        Scene scene = new Scene(loader.load());
//        primaryStage.setScene(scene);
//        primaryStage.setTitle(WindowsController.VIEW_TITLE);
//        primaryStage.show();
//    }
}
