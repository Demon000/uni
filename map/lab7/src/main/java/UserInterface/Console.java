package UserInterface;

import Domain.Assignment;
import Domain.Grade;
import Domain.Student;
import Service.CommonService;
import Service.CommonServiceException;
import Time.UniversityYearError;
import Validator.ValidationException;
import java.time.LocalDate;
import java.util.List;
import java.util.Optional;

import static Utils.InputUtils.*;

interface ConsoleMenuCallable {
    void call() throws Exception;
}

class ConsoleMenuEntry {
    private final String index;
    private final String description;
    private final boolean repeatOnError;
    private final ConsoleMenuCallable callable;

    public ConsoleMenuEntry(String index, String description, ConsoleMenuCallable callable, boolean repeatOnError) {
        this.index = index;
        this.description = description;
        this.repeatOnError = repeatOnError;
        this.callable = callable;
    }

    public ConsoleMenuEntry(String index, String description, ConsoleMenuCallable callable) {
        this(index, description, callable, false);
    }

    public String getIndex() {
        return index;
    }

    public void call() {
        while (true) {
            try {
                callable.call();
                break;
            } catch (Exception e) {
                System.out.println(e.getMessage());
                if (!repeatOnError) {
                    break;
                }
            }
        }
    }

    public boolean isExit() {
        return index.equals("x");
    }

    public String toString() {
        return String.format("%s. %s", index, description);
    }
}

public class Console {
    private final List<ConsoleMenuEntry> mainEntries;
    private final List<ConsoleMenuEntry> studentEntries;
    private final List<ConsoleMenuEntry> assignmentEntries;
    private final List<ConsoleMenuEntry> gradeEntries;
    private final List<ConsoleMenuEntry> filterEntries;
    private final CommonService service;

    public Console(CommonService service) {
        this.service = service;

        studentEntries = List.of(
                new ConsoleMenuEntry("1", "Add student", this::addStudent),
                new ConsoleMenuEntry("2", "List students", this::listStudents),
                new ConsoleMenuEntry("3", "Update student", this::updateStudent),
                new ConsoleMenuEntry("4", "Add student motivated week", this::addStudentMotivatedWeek),
                new ConsoleMenuEntry("5", "Remove student motivated week", this::removeStudentMotivatedWeek),
                new ConsoleMenuEntry("6", "Delete student", this::deleteStudent),
                new ConsoleMenuEntry("x", "Back", this::submenuExit)
        );

        assignmentEntries = List.of(
                new ConsoleMenuEntry("1", "Add assignment", this::addAssignment),
                new ConsoleMenuEntry("2", "List assignments", this::listAssignments),
                new ConsoleMenuEntry("3", "Update assignment", this::updateAssignment),
                new ConsoleMenuEntry("4", "Delete assignment", this::deleteAssignment),
                new ConsoleMenuEntry("x", "Back", this::submenuExit)
        );

        gradeEntries = List.of(
                new ConsoleMenuEntry("1", "Add grade", this::addGrade),
                new ConsoleMenuEntry("2", "List grades", this::listGrades),
                new ConsoleMenuEntry("3", "Update grade", this:: updateGrade),
                new ConsoleMenuEntry("4", "Delete grade", this::deleteGrade),
                new ConsoleMenuEntry("x", "Back", this::submenuExit)
        );

        filterEntries = List.of(
                new ConsoleMenuEntry("1", "Show students by group", this::showStudentsByGroup),
                new ConsoleMenuEntry("2", "Show students with an assignment", this::showStudentsWithAssignment),
                new ConsoleMenuEntry("3", "Show students with an assignment turned in to a professor", this::showStudentsWithAssignmentProfessor),
                new ConsoleMenuEntry("4", "Show students with an assignment turned in at a specific week", this::showGradesAtAssignmentAtWeek),
                new ConsoleMenuEntry("x", "Back", this::submenuExit)
        );

        mainEntries = List.of(
                new ConsoleMenuEntry("1", "Students", () -> {
                    runEntries(studentEntries);
                }),
                new ConsoleMenuEntry("2", "Assignments", () -> {
                    runEntries(assignmentEntries);
                }),
                new ConsoleMenuEntry("3", "Grades", () -> {
                    runEntries(gradeEntries);
                }),
                new ConsoleMenuEntry("4", "Filters", () -> {
                    runEntries(filterEntries);
                }),
                new ConsoleMenuEntry("x", "Exit", this::menuExit)
        );
    }

    private void menuExit() {
        System.out.println("Goodbye!");
    }
    private void submenuExit() {}

    private ConsoleMenuEntry getEntryByIndex(List<ConsoleMenuEntry> entries, String index) {
        Optional<ConsoleMenuEntry> entry = entries
                .stream()
                .filter(e -> index.equals(e.getIndex()))
                .findFirst();

        if (entry.isEmpty()) {
            return null;
        }

        return entry.get();
    }

    private ConsoleMenuEntry readEntry(List<ConsoleMenuEntry> entries) {
        String index = readString("Command: ", "Invalid command");
        return getEntryByIndex(entries, index);
    }

    private void addStudent() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        String firstName = readString("First name: ", "Invalid first name");
        String lastName = readString("Last name: ", "Invalid last name");
        String email = readString("Email: ", "Invalid email");
        String group = readString("Group: ", "Invalid group");
        String professorName = readString("Professor name: ", "Invalid professor name");

        Student student = service.addStudent(id, firstName, lastName, email, group, professorName);
        System.out.println(String.format("Added: %s", student));
    }

    private void listStudents() {
        System.out.println("All students:");
        service.getStudents().forEach(System.out::println);
    }

    private void updateStudent() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        String firstName = readString("New first name (empty to leave unchanged): ");
        String lastName = readString("New last name (empty to leave unchanged): ");
        String email = readString("New email (empty to leave unchanged): ");
        String group = readString("New group (empty to leave unchanged): ");
        String professorName = readString("New professor name (empty to leave unchanged): ");

        Student student = service.updateStudent(id, firstName, lastName, email, group, professorName);
        System.out.println(String.format("Updated: %s", student));
    }

    private void addStudentMotivatedWeek() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        long week = readNatural("Week: ", "Invalid week");

        Student student = service.addStudentMotivatedWeek(id, week);
        System.out.println(String.format("Updated: %s", student));
    }

    private void removeStudentMotivatedWeek() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        long week = readNatural("Week: ", "Invalid week");

        Student student = service.removeStudentMotivatedWeek(id, week);
        System.out.println(String.format("Updated: %s", student));
    }

    private void deleteStudent() throws CommonServiceException {
        String id = readString("Id: ", "Invalid id");

        Student student = service.deleteStudent(id);
        System.out.println(String.format("Deleted: %s", student));
    }

    private void showStudentsByGroup() {
        String group = readString("Group: ", "Invalid group");
        System.out.println("Students with group:");
        service.getStudentsForGroup(group).forEach(System.out::println);
    }

    private void showStudentsWithAssignment() {
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        System.out.println("Students with assignment:");
        service.getStudentsWithAssignment(assignmentId).forEach(System.out::println);
    }

    private void showStudentsWithAssignmentProfessor() {
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        String professorName = readString("Professor name: ", "Invalid professor name");
        System.out.println("Students with assignment turned in at professor:");
        service.getStudentsWithAssignmentProfessor(assignmentId, professorName).forEach(System.out::println);
    }

    private void addAssignment() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        String description = readString("Description: ", "Invalid description");
        long startWeek = readNatural("Start week: ", "Invalid start week");
        long deadlineWeek = readNatural("Deadline week: ", "Invalid deadline week");

        Assignment assignment = service.addAssignment(id, description, startWeek, deadlineWeek);
        System.out.println(String.format("Added: %s", assignment));
    }

    private void listAssignments() {
        System.out.println("All assignments:");
        service.getAssignments().forEach(System.out::println);
    }

    private void updateAssignment() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        String description = readString("Description (empty to leave unchanged): ");
        long startWeek = readNatural("Start week (empty to leave unchanged): ");
        long deadlineWeek = readNatural("Deadline week (empty to leave unchanged): ");

        Assignment assignment = service.updateAssignment(id, description, startWeek, deadlineWeek);
        System.out.println(String.format("Updated: %s", assignment));
    }

    private void deleteAssignment() throws CommonServiceException {
        String id = readString("Id: ", "Invalid id");

        Assignment assignment = service.deleteAssignment(id);
        System.out.println(String.format("Deleted: %s", assignment));
    }

    private void addGrade() throws CommonServiceException, ValidationException, UniversityYearError {
        String studentId = readString("Student id: ", "Invalid student id");
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        LocalDate date = readDate("Date (empty to use today's date): ");

        long penalty = service.getGradePenalty(studentId, assignmentId, date);
        if (penalty > 0) {
            System.out.println(String.format("A penalty of %d points will be applied to the grade.", penalty));
        }

        int value = readNatural("Grade: ", "Invalid grade");

        String professorName = readString("Professor name: ");
        String feedback = readString("Feedback (can be empty): ");

        Grade grade = service.addGrade(studentId, assignmentId, date, value, professorName, feedback);
        System.out.println(String.format("Added: %s", grade));
    }

    private void listGrades() {
        System.out.println("All grades:");
        service.getGrades().forEach(System.out::println);
    }

    private void updateGrade() throws CommonServiceException, ValidationException, UniversityYearError {
        String studentId = readString("Student id: ", "Invalid student id");
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        LocalDate date = readDate("New date (empty to leave unchanged): ");

        long penalty = service.getGradePenalty(studentId, assignmentId, date);
        if (penalty > 0) {
            System.out.println(String.format("A penalty of %d points will be applied to the grade.", penalty));
        }

        int value = readNatural("New grade: (empty to leave unchanged): ");

        String professorName = readString("New professor name (empty to leave unchanged): ");
        String feedback = readString("New feedback (empty to leave unchanged): ");

        Grade grade = service.updateGrade(studentId, assignmentId, date, value, professorName, feedback);
        System.out.println(String.format("Updated: %s", grade));
    }

    private void deleteGrade() throws CommonServiceException {
        String studentId = readString("Student id: ", "Invalid student id");
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");

        Grade grade = service.deleteGrade(studentId, assignmentId);
        System.out.println(String.format("Deleted: %s", grade));
    }

    private void showGradesAtAssignmentAtWeek() {
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        long week = readNatural("Week: ", "Invalid week");
        System.out.println("Grades for assignment turned it at week:");
        service.getGradesAtAssignmentInWeek(assignmentId, week).forEach(System.out::println);
    }

    private void populate() {
        try {
            Student student = service.addStudent("1", "Cosmin", "Tanislav",
                    "tcir2625@scs.ubbcluj.ro", "227", "Sergiu");
//            student.addMotivatedWeek(1);
//            student.addMotivatedWeek(14);
//            student.addMotivatedWeek(3);
            service.addAssignment("1", "Iteratia 1", 7, 9);
        } catch (CommonServiceException | ValidationException e) {
            //e.printStackTrace();
        }
    }

    private void printEntries(List<ConsoleMenuEntry> entries) {
        System.out.println("Menu:");
        entries.forEach(System.out::println);
    }

    public void runEntries(List<ConsoleMenuEntry> entries) {
        while (true) {
            printEntries(entries);
            ConsoleMenuEntry entry = readEntry(entries);

            if (entry == null) {
                System.out.println("Invalid command");
                continue;
            }

            if (entry.isExit()) {
                break;
            }

            entry.call();
        }
    }

    public void run() {
        populate();
        runEntries(mainEntries);
    }
}
