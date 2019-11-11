package Tests;

import Domain.BaseEntity;
import Domain.Student;
import Repository.BaseRepository;
import Time.UniversitySemester;
import Time.UniversityYear;
import Time.UniversityYearError;
import Validator.*;
import org.junit.Test;

import java.time.LocalDate;

import static org.junit.Assert.*;

public class Tests {
    @Test
    public void testBaseValidator() {
        BaseEntityStringValidator<BaseEntity<String>> validator = new BaseEntityStringValidator<>();

        // Test id validation
        try {
            validator.validateId("123");
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateId("123+123");
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateId("c123");
            fail();
        } catch (ValidationException e) {
        }
    }

    @Test
    public void testStudentValidator() {
        StudentValidator validator = new StudentValidator();

        // Test name validation
        try {
            validator.validateName("Cosmin");
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateName("Co");
            fail();
        } catch (ValidationException e) {
        }

        try {
            validator.validateName("F123");
            fail();
        } catch (ValidationException e) {
        }

        // Test email validation
        try {
            validator.validateEmail("tcir2625@scs.ubbcluj.ro");
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateName("fail@scs.ubbcluj.ro");
            fail();
        } catch (ValidationException e) {
        }
    }

    private UniversityYear createUniversityYear() {
        UniversitySemester firstSemester;
        UniversitySemester secondSemester;

        try {
            firstSemester = UniversitySemester.fromLocalDates(
                    LocalDate.of(2019, 9, 30), LocalDate.of(2019, 12, 20),
                    LocalDate.of(2020, 1, 6), LocalDate.of(2020, 1, 17)
            );

            secondSemester = UniversitySemester.fromLocalDates(
                    LocalDate.of(2020, 2, 24), LocalDate.of(2020, 4, 17),
                    LocalDate.of(2020, 4, 27), LocalDate.of(2020, 6, 5)
            );
        } catch (Exception e) {
            fail();
            return null;
        }

        return new UniversityYear(firstSemester, secondSemester);
    }

    @Test
    public void testUniversityYear() {
        UniversityYear year = createUniversityYear();
        if (year == null) {
            fail();
        }

        assertEquals(year.getNumberOfWeeks(), 28);
    }

    @Test
    public void testAssignmentValidator() {
        UniversityYear year = createUniversityYear();
        AssignmentValidator validator = new AssignmentValidator(year);

        // Test description validation
        try {
            validator.validateDescription("This is a valid description.");
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateDescription("This no.");
            fail();
        } catch (ValidationException e) {
        }

        LocalDate today = LocalDate.now();
        long currentWeek = 0;
        try {
            currentWeek = year.getWeeksSinceStart(today);
        } catch (UniversityYearError e) {
            fail();
        }

        // Test weeks validation
        try {
            validator.validateWeeksRelative(currentWeek, currentWeek + 1);
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateWeeksRelative(currentWeek + 1, currentWeek);
            fail();
        } catch (ValidationException e) {
        }

        try {
            validator.validateWeeksRelative(currentWeek - 2, currentWeek - 1);
            fail();
        } catch (ValidationException e) {
        }
    }

    @Test
    public void testGradeValidator() {
        GradeValidator validator = new GradeValidator();

        try {
            validator.validateValue(1);
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateValue(10);
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateValue(0);
            fail();
        } catch (ValidationException e) {
        }

        try {
            validator.validateValue(11);
            fail();
        } catch (ValidationException e) {
        }

        try {
            validator.validateValue(0);
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateValue(2);
        } catch (ValidationException e) {
            fail();
        }

        try {
            validator.validateValue(-1);
            fail();
        } catch (ValidationException e) {
        }

        try {
            validator.validateValue(3);
            fail();
        } catch (ValidationException e) {
        }
    }

    @Test
    public void testBaseRepository() {
        StudentValidator validator = new StudentValidator();
        BaseRepository<String, Student, StudentValidator> repository = new BaseRepository<>(validator);
        Student student, saved, retrieved;

        // Test null checks
        try {
            repository.findOne(null);
            fail();
        } catch (IllegalArgumentException e) {
        }

        try {
            repository.save(null);
            fail();
        } catch (IllegalArgumentException | ValidationException e) {
        }

        try {
            repository.delete(null);
            fail();
        } catch (IllegalArgumentException e) {
        }

        try {
            repository.update(null);
            fail();
        } catch (IllegalArgumentException | ValidationException e) {
        }

        // Validate saving a student and null return
        student = new Student("1", "Cosmin", "Tanislav", "tcir2625@scs.ubbcluj.ro");
        try {
            retrieved = repository.save(student);
            assertNull(retrieved);
        } catch (ValidationException e) {
            fail();
        }

        // Validate saving a new student with same id and old student return
        saved = student;
        student = new Student("1", "Nimcos", "Tanislav", "tcir2625@scs.ubbcluj.ro");
        try {
            retrieved = repository.save(student);
            assertEquals(saved, retrieved);
        } catch (ValidationException e) {
            fail();
        }

        // Validate finding the new student student using id
        retrieved = repository.findOne("1");
        assertEquals(retrieved, student);

        // Validate updating a non existent student
        student = new Student("2", "Cosmin", "Tanislav", "tcir2625@scs.ubbcluj.ro");
        try {
            retrieved = repository.update(student);
            assertEquals(retrieved, student);
        } catch (ValidationException e) {
            fail();
        }

        // Validate updating an existing student
        student = new Student("1", "Cosmin", "Tanislav", "tcir2625@scs.ubbcluj.ro");
        try {
            retrieved = repository.update(student);
            assertNull(retrieved);
        } catch (ValidationException e) {
            fail();
        }

        // Validate deleting a student
        retrieved = repository.delete("1");
        assertEquals(retrieved, student);

        // Validate deleting a non existent student
        retrieved = repository.delete("1");
        assertNull(retrieved);

        // Validate finding all students
        try {
            repository.save(new Student("1", "Cosmin", "Tanislav", "tcir2625@scs.ubbcluj.ro"));
            repository.save(new Student("2", "Teodor", "Spiridon", "tsir2425@scs.ubbcluj.ro"));
            repository.save(new Student("3", "Mihai", "Solcan", "smir2325@scs.ubbcluj.ro"));
        } catch (ValidationException e) {
            fail();
        }

        int i = 1;
        for (Student s : repository.findAll()) {
            assertEquals(s.getId(), String.valueOf(i));
            i++;
        }
    }

    @Test
    public void testAll() {
        testBaseValidator();
        testBaseRepository();
        testUniversityYear();
        testStudentValidator();
        testAssignmentValidator();
    }
}
