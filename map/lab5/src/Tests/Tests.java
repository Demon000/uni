package Tests;

import Domain.Student;
import Validator.StudentValidator;
import Validator.ValidationException;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class Tests {
    @Test
    public void testStudent() {
        Student student = new Student("1", "Mihai", "Andrei", "mhir2221@scs.ubbcluj.ro");
        assertEquals(student.getId(), "1");
        assertEquals(student.getFirstName(), "Mihai");
        assertEquals(student.getLastName(), "Andrei");
        assertEquals(student.getEmail(), "mhir2221@scs.ubbcluj.ro");

        student.setId("2");
        assertEquals(student.getId(), "1");

        student.setFirstName("Teodor");
        assertEquals(student.getFirstName(), "Teodor");

        student.setLastName("Spiridor");
        assertEquals(student.getLastName(), "Spiridon");

        student.setEmail("st2221@scs.ubbcluj.ro");
        assertEquals(student.getEmail(), "st2221@scs.ubbcluj.ro");
    }

    public void testStudentValidator() {
        StudentValidator validator = new StudentValidator();

        // Test id validation
        try {
            validator.validateId("123");
            assertTrue(true);
        } catch (ValidationException e) {
            assertTrue(false);
            e.printStackTrace();
        }

        try {
            validator.validateId("c123");
            assertTrue(false);
        } catch (ValidationException e) {
            assertTrue(true);
        }

        // Test name validation
        try {
            validator.validateName("Cosmin");
            assertTrue(true);
        } catch (ValidationException e) {
            assertTrue(false);
            e.printStackTrace();
        }

        try {
            validator.validateName("Cosmin - Gabriel");
            assertTrue(true);
        } catch (ValidationException e) {
            assertTrue(false);
            e.printStackTrace();
        }

        try {
            validator.validateName("Co");
            assertTrue(false);
        } catch (ValidationException e) {
            assertTrue(true);
        }

        try {
            validator.validateName("Cosmin1");
            assertTrue(false);
        } catch (ValidationException e) {
            assertTrue(true);
        }

        // Test email validation

    }

    public void testAssignment() {

    }

    public void testAll() {
        testStudent();
    }
}
