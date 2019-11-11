package Service;

import Domain.Assignment;
import Domain.Grade;
import Domain.Student;
import Repository.AssignmentRepository;
import Repository.GradeRepository;
import Repository.StudentRepository;
import Time.UniversityYear;
import Validator.ValidationException;

import java.time.LocalDate;

public class CommonService {
    private StudentRepository studentRepository;
    private AssignmentRepository assignmentRepository;
    private GradeRepository gradeRepository;
    private UniversityYear year;

    public CommonService(StudentRepository studentRepository, AssignmentRepository assignmentRepository,
                         GradeRepository gradeRepository, UniversityYear year) {
        this.studentRepository = studentRepository;
        this.assignmentRepository = assignmentRepository;
        this.gradeRepository = gradeRepository;
        this.year = year;
    }

    /**
     * Add a student.
     * @param id the id of the student
     * @param firstName the first name of the student
     * @param lastName the last name of the student
     * @param email the email of the student
     * @return the newly created student
     * @throws CommonServiceException if a student with the given id already exists
     * @throws ValidationException if the student is invalid
     */
    public Student addStudent(String id, String firstName, String lastName, String email)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student != null) {
            throw new CommonServiceException(String.format("Student with id %s already exists.", id));
        }

        student = new Student(id, firstName, lastName, email);
        studentRepository.save(student);
        return student;
    }

    /**
     * Get a student given its id.
     * @param id the student id to look for
     * @return the student
     * @throws CommonServiceException if a student with the given id already exists
     */
    public Student getStudentById(String id) throws CommonServiceException {
        Student student = studentRepository.findOne(id);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", id));
        }

        return student;
    }

    /**
     * Get all the students.
     * @return an iterable of all the students.
     */
    public Iterable<Student> getStudents() {
        return studentRepository.findAll();
    }

    /**
     * Update a student.
     * @param id the student id
     * @param firstName the new first name of the student, can be null or empty to not update it
     * @param lastName the new last name of the student, can be null or empty to not update it
     * @param email the new email of the student, can be null or empty to not update it
     * @return the updated student
     * @throws CommonServiceException if the student doesn't exist
     * @throws ValidationException if the updated student is invalid
     */
    public Student updateStudent(String id, String firstName, String lastName, String email)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", id));
        }

        if (firstName == null || !firstName.isEmpty()) {
            student.setFirstName(firstName);
        }

        if (lastName == null || !lastName.isEmpty()) {
            student.setLastName(lastName);
        }

        if (email == null || !email.isEmpty()) {
            student.setEmail(email);
        }

        studentRepository.update(student);

        return student;
    }

    /**
     * Delete a student.
     * @param id the student id
     * @return the deleted student
     * @throws CommonServiceException if the student does not exist
     */
    public Student deleteStudent(String id) throws CommonServiceException {
        Student student = studentRepository.findOne(id);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", id));
        }

        return studentRepository.delete(id);
    }

    /**
     * Add an assignment.
     * @param id the assignment id
     * @param description the description of the assignment
     * @param startWeek the start week of the assignment
     * @param deadlineWeek the deadline week of the assignment
     * @return the newly created assignment
     * @throws CommonServiceException if the assignment does not exist
     * @throws ValidationException if the assignment is not valid
     */
    public Assignment addAssignment(String id, String description, long startWeek, long deadlineWeek)
            throws CommonServiceException, ValidationException {
        Assignment assignment = assignmentRepository.findOne(id);
        if (assignment != null) {
            throw new CommonServiceException(String.format("Assignment with id %s already exists.", id));
        }

        assignment = new Assignment(id, description, startWeek, deadlineWeek);
        assignmentRepository.save(assignment);
        return assignment;
    }

    /**
     * Get an assignment by id.
     * @param id the assignment id
     * @return the assignment
     * @throws CommonServiceException if the assignment does not exist
     */
    public Assignment getAssignmentById(String id) throws CommonServiceException {
        Assignment assignment = assignmentRepository.findOne(id);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", id));
        }

        return assignment;
    }

    /**
     * Get all the assignments.
     * @return an iterable of all the assignments
     */
    public Iterable<Assignment> getAssignments() {
        return assignmentRepository.findAll();
    }

    /**
     * Update an assignment.
     * @param id the id of the assignment
     * @param description the new description of the assignment, can be null or empty to not update it
     * @param startWeek the new start week of the assignment, can be 0 to not update it
     * @param deadlineWeek the new deadline week of the assignment, can be 0 to not update it
     * @return the updated assignment
     * @throws CommonServiceException if the assignment does not exist
     * @throws ValidationException if the assignment is not valid
     */
    public Assignment updateAssignment(String id, String description, long startWeek, long deadlineWeek)
            throws CommonServiceException, ValidationException {
        Assignment assignment = assignmentRepository.findOne(id);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", id));
        }

        if (!description.isEmpty()) {
            assignment.setDescription(description);
        }

        if (startWeek != 0) {
            assignment.setStartWeek(startWeek);
        }

        if  (deadlineWeek != 0) {
            assignment.setDeadlineWeek(deadlineWeek);
        }

        assignmentRepository.update(assignment);

        return assignment;
    }

    /**
     * Delete an assignment.
     * @param id the id of the assignment
     * @return the deleted assignment
     * @throws CommonServiceException if the assignment does not exist
     */
    public Assignment deleteAssignment(String id) throws CommonServiceException {
        Assignment assignment = assignmentRepository.findOne(id);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", id));
        }

        assignmentRepository.delete(id);
        return assignment;
    }

    /**
     * Add a grade.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of the assignment at which the student received this grade
     * @param value the value of the grade
     * @param date the date the student received this grade on
     * @return the newly created grade
     * @throws CommonServiceException if the student or assignment do not exist, or if the grade already exists
     * @throws ValidationException if the grade is invalid
     */
    public Grade addGrade(String studentId, String assignmentId, int value, LocalDate date)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", assignmentId));
        }

        String gradeId = studentId + assignmentId;
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade != null) {
            throw new CommonServiceException(String.format("Grade with id %s already exists.", gradeId));
        }

        long penalty = year.getWeeksSinceStart(date) - assignment.getDeadlineWeek();
        if (penalty < 0) {
            penalty = 0;
        }

        if (date == null) {
            date = LocalDate.now();
        }

        grade = new Grade(gradeId, value, penalty, date);
        gradeRepository.save(grade);
        return grade;
    }

    /**
     * Get a grade by id.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of the assignment at which the student received this grade
     * @return the grade
     * @throws CommonServiceException if the student, assignment or grade do not exist
     */
    public Grade getGradeById(String studentId, String assignmentId) throws CommonServiceException {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", assignmentId));
        }

        String gradeId = studentId + assignmentId;
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade == null) {
            throw new CommonServiceException(String.format("Grade with id %s already exists.", gradeId));
        }

        return grade;
    }

    /**
     * Get all the grades.
     * @return an iterable with all the grades
     */
    public Iterable<Grade> getGrades() {
        return gradeRepository.findAll();
    }

    /**
     * Update a grade.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of this assignment at which the student received this grade
     * @param value the new value of this grade, can be 0 to not update it
     * @param date the new date of this grade, can be null to not update id
     * @return the updated grade
     * @throws CommonServiceException if the student, assignment or grade do not exist
     * @throws ValidationException if the grade is invalid
     */
    public Grade updateGrade(String studentId, String assignmentId, int value, LocalDate date)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", assignmentId));
        }

        String gradeId = studentId + assignmentId;
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade == null) {
            throw new CommonServiceException(String.format("Grade with id %s does not exist.", gradeId));
        }

        if (value != 0) {
            grade.setValue(value);
        }

        if (date != null) {
            grade.setDate(date);
        }

        gradeRepository.update(grade);
        return grade;
    }

    /**
     * Delete a grade.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of this assignment at which the student received this grade
     * @return the deleted grade
     * @throws CommonServiceException if the student, assignment or grade do not exist
     */
    public Grade deleteGrade(String studentId, String assignmentId) throws CommonServiceException {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist.", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist.", assignmentId));
        }

        String gradeId = studentId + assignmentId;
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade == null) {
            throw new CommonServiceException(String.format("Grade with id %s does not exist.", gradeId));
        }

        gradeRepository.delete(gradeId);
        return grade;
    }
}
