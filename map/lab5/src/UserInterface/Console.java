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

import static UserInterface.ConsoleInputUtils.*;

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
    private final List<ConsoleMenuEntry> entries;
    private final CommonService service;

    public Console(CommonService service) {
        this.service = service;

        entries = List.of(
                new ConsoleMenuEntry("1", "Add student", this::addStudent),
                new ConsoleMenuEntry("2", "List students", this::listStudents),
                new ConsoleMenuEntry("3", "Update student", this::updateStudent),
                new ConsoleMenuEntry("4", "Delete student", this::deleteStudent),
                new ConsoleMenuEntry("5", "Add assignment", this::addAssignment),
                new ConsoleMenuEntry("6", "List assignments", this::listAssignments),
                new ConsoleMenuEntry("7", "Update assignment", this::updateAssignment),
                new ConsoleMenuEntry("8", "Delete assignment", this::deleteAssignment),
                new ConsoleMenuEntry("9", "Add grade", this::addGrade),
                new ConsoleMenuEntry("10", "List grades", this::listGrades),
                new ConsoleMenuEntry("11", "Update grade", this:: updateGrade),
                new ConsoleMenuEntry("12", "Delete grade", this::deleteGrade),
                new ConsoleMenuEntry("x", "Exit", this::exit)
        );
    }

    private void exit() {
        System.out.println("Goodbye!");
    }

    private ConsoleMenuEntry getEntryByIndex(String index) {
        Optional<ConsoleMenuEntry> entry = entries
                .stream()
                .filter(e -> index.equals(e.getIndex()))
                .findFirst();

        if (entry.isEmpty()) {
            return null;
        }

        return entry.get();
    }

    private ConsoleMenuEntry readEntry() {
        String index = readString("Command: ", "Invalid command");
        return getEntryByIndex(index);
    }

    private void addStudent() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        String firstName = readString("First name: ", "Invalid first name");
        String lastName = readString("Last name: ", "Invalid last name");
        String email = readString("Email: ", "Invalid email");
        String group = readString("Group: ", "Invalid group");

        Student student = service.addStudent(id, firstName, lastName, email, group);
        System.out.println(String.format("Added: %s", student));
    }

    private void listStudents() {
        service.getStudents().forEach(System.out::println);
    }

    public void updateStudent() throws CommonServiceException, ValidationException {
        String id = readString("Id: ", "Invalid id");
        String firstName = readString("New first name (empty to leave unchanged): ");
        String lastName = readString("New last name (empty to leave unchanged): ");
        String email = readString("New email (empty to leave unchanged): ");
        String group = readString("New group (empty to leave unchanged): ");

        Student student = service.updateStudent(id, firstName, lastName, email, group);
        System.out.println(String.format("Updated: %s", student));
    }

    public void deleteStudent() throws CommonServiceException {
        String id = readString("Id: ", "Invalid id");

        Student student = service.deleteStudent(id);
        System.out.println(String.format("Deleted: %s", student));
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

    public void addGrade() throws CommonServiceException, ValidationException, UniversityYearError {
        String studentId = readString("Student id: ", "Invalid student id");
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        LocalDate date = readDate("Date (empty to use today's date): ");

        long penalty = service.getGradePenalty(assignmentId, date);
        if (penalty > 0) {
            System.out.println(String.format("A penalty of %d points will be applied to the grade.", penalty));
        }

        int value = readNatural("Grade: ", "Invalid grade");

        String feedback = readString("Feedback (can be empty): ");

        Grade grade = service.addGrade(studentId, assignmentId, date, value, feedback);
        System.out.println(String.format("Added: %s", grade));
    }

    private void listGrades() {
        service.getGrades().forEach(System.out::println);
    }

    public void updateGrade() throws CommonServiceException, ValidationException, UniversityYearError {
        String studentId = readString("Student id: ", "Invalid student id");
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");
        LocalDate date = readDate("New date (empty to leave unchanged): ");

        long penalty = service.getGradePenalty(assignmentId, date);
        if (penalty > 0) {
            System.out.println(String.format("A penalty of %d points will be applied to the grade.", penalty));
        }

        int value = readNatural("New grade: (empty to leave unchanged): ");

        String feedback = readString("New feedback (empty to leave unchanged): ");

        Grade grade = service.updateGrade(studentId, assignmentId, date, value, feedback);
        System.out.println(String.format("Updated: %s", grade));
    }

    public void deleteGrade() throws CommonServiceException {
        String studentId = readString("Student id: ", "Invalid student id");
        String assignmentId = readString("Assignment id: ", "Invalid assignment id");

        Grade grade = service.deleteGrade(studentId, assignmentId);
        System.out.println(String.format("Deleted: %s", grade));
    }

    private void printEntries() {
        System.out.println("Menu: ");
        entries.forEach(System.out::println);
    }

    private void populate() {
        try {
            service.addStudent("1", "Cosmin", "Tanislav", "tcir2625@scs.ubbcluj.ro", "227");
            service.addAssignment("1", "Iteratia 1", 7, 9);
        } catch (CommonServiceException | ValidationException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        populate();

        while (true) {
            printEntries();
            ConsoleMenuEntry entry = readEntry();

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
}
