package service;

import domain.Assignment;
import domain.Grade;
import domain.Student;
import repository.BaseRepository;
import time.UniversityYear;
import time.UniversityYearError;
import validator.AssignmentValidator;
import validator.GradeValidator;
import validator.StudentValidator;
import validator.ValidationException;

import java.time.LocalDate;
import java.util.List;
import java.util.stream.Collectors;

import static utils.CollectionUtils.streamFromIterable;

public class CommonService {
    private final BaseRepository<String, Student, StudentValidator> studentRepository;
    private final BaseRepository<String, Assignment, AssignmentValidator> assignmentRepository;
    private final BaseRepository<String, Grade, GradeValidator> gradeRepository;
    private final UniversityYear year;

    public CommonService(BaseRepository<String, Student, StudentValidator> studentRepository,
                         BaseRepository<String, Assignment, AssignmentValidator> assignmentRepository,
                         BaseRepository<String, Grade, GradeValidator> gradeRepository,
                         UniversityYear year) {
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
    public Student addStudent(String id, String firstName, String lastName, String email, String group, String professorName)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student != null) {
            throw new CommonServiceException(String.format("Student with id %s already exists", id));
        }

        student = new Student(id, firstName, lastName, email, group, professorName);

        studentRepository.save(student);
        
        return student;
    }

    /**
     * Add a motivated week for a student.
     * @param id id the id of the student
     * @param week the week to add
     * @return the updated student
     * @throws CommonServiceException if a student with the given id does not exist
     * @throws ValidationException if the student is invalid
     */
    public Student addStudentMotivatedWeek(String id, long week) throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist", id));
        }

        student.addMotivatedWeek(week);

        studentRepository.update(student);
        
        return student;
    }

    /**
     * Remove a motivated week for a student.
     * @param id id the id of the student
     * @param week the week to remove
     * @return the updated student
     * @throws CommonServiceException if a student with the given id does not exist
     * @throws ValidationException if the student is invalid
     */
    public Student removeStudentMotivatedWeek(String id, long week) throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist", id));
        }

        student.removeMotivatedWeek(week);

        studentRepository.update(student);
        
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
     * @param group the new group of the student, can be null or empty to not update it
     * @param professorName the new professor name of the student, can be null or empty to not update it
     * @param motivatedWeeks the new motivated weeks of the student, can be null to not update it
     * @return the updated student
     * @throws CommonServiceException if the student doesn't exist
     * @throws ValidationException if the updated student is invalid
     */
    public Student updateStudent(String id, String firstName, String lastName, String email, String group,
                                 String professorName, List<Long> motivatedWeeks)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist", id));
        }

        if (firstName != null && !firstName.isEmpty()) {
            student.setFirstName(firstName);
        }

        if (lastName != null && !lastName.isEmpty()) {
            student.setLastName(lastName);
        }

        if (email != null && !email.isEmpty()) {
            student.setEmail(email);
        }

        if (group != null && !group.isEmpty()) {
            student.setGroup(group);
        }

        if (professorName != null && !professorName.isEmpty()) {
            student.setProfessorName(professorName);
        }

        if (motivatedWeeks != null) {
            student.setMotivatedWeeks(motivatedWeeks);
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
            throw new CommonServiceException(String.format("Student with id %s does not exist", id));
        }

        studentRepository.delete(id);
        
        return student;
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
            throw new CommonServiceException(String.format("Assignment with id %s already exists", id));
        }

        assignment = new Assignment(id, description, startWeek, deadlineWeek);

        assignmentRepository.save(assignment);
        
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
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", id));
        }

        if (description != null && !description.isEmpty()) {
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
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", id));
        }

        assignmentRepository.delete(id);
        
        return assignment;
    }

    /**
     * Get the penalty that will be added for an assignment if it were to be turned in at a specific date.
     * @param studentId the id of the student
     * @param assignmentId the id of the assignment
     * @param date the date the assignment will be turned in, can be null to use today's date
     * @return the number of weeks that will pass until the given date
     * @throws CommonServiceException if the student or assignment do not exist
     * @throws UniversityYearError if the given date is not part of the current semester
     */
    public long getGradePenalty(String studentId, String assignmentId, LocalDate date) throws CommonServiceException, UniversityYearError {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", assignmentId));
        }

        if (date == null) {
            date = LocalDate.now();
        }

        long startWeek = assignment.getStartWeek();
        long deadlineWeek = assignment.getDeadlineWeek();
        long penalty = year.getWeeksSinceStart(date) - deadlineWeek;

        if (penalty < 0) {
            penalty = 0;
        }

        if (penalty > 0) {
            List<Long> motivatedWeeks = student.getMotivatedWeeks();

            for (Long w : motivatedWeeks) {
                long week = w;

                if (week >= startWeek && week <= deadlineWeek) {
                    penalty--;
                }
            }
        }

        if (penalty < 0) {
            penalty = 0;
        }

        return penalty;
    }

    /**
     * Add a grade.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of the assignment at which the student received this grade
     * @param date the date the student received this grade on, can be null to use today's date
     * @param value the value of the grade
     * @param professorName the name of the professor that added the grade
     * @param feedback the feedback of the grade, can be null to use an empty string
     * @return the newly created grade
     * @throws CommonServiceException if the student or assignment do not exist, or if the grade already exists
     * @throws ValidationException if the grade is invalid
     */
    public Grade addGrade(String studentId, String assignmentId, LocalDate date, int value,
                          String professorName, String feedback)
            throws CommonServiceException, ValidationException, UniversityYearError {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", assignmentId));
        }

        String gradeId = Grade.createCompositeId(studentId, assignmentId);
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade != null) {
            throw new CommonServiceException(String.format("Grade with id %s already exists", gradeId));
        }

        if (date == null) {
            date = LocalDate.now();
        }

        long penalty = getGradePenalty(studentId, assignmentId, date);

        if (feedback == null) {
            feedback = "";
        }

        grade = new Grade(gradeId, date, penalty, value, professorName, feedback);

        gradeRepository.save(grade);
        
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
     * @param date the new date of this grade, can be null to not update it
     * @param professorName the new name of the professor that added the grade, can be null or empty to not update it
     * @param feedback the new feedback of this grade, can be null to not update it
     * @return the updated grade
     * @throws CommonServiceException if the student, assignment or grade do not exist
     * @throws ValidationException if the grade is invalid
     */
    public Grade updateGrade(String studentId, String assignmentId, LocalDate date, int value,
                             String professorName, String feedback)
            throws CommonServiceException, ValidationException, UniversityYearError {
        Student student = studentRepository.findOne(studentId);
        if (student == null) {
            throw new CommonServiceException(String.format("Student with id %s does not exist", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", assignmentId));
        }

        String gradeId = Grade.createCompositeId(studentId, assignmentId);
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade == null) {
            throw new CommonServiceException(String.format("Grade with id %s does not exist", gradeId));
        }

        if (date != null) {
            grade.setDate(date);
        } else {
            date = grade.getDate();
        }

        long penalty = getGradePenalty(studentId, assignmentId, date);
        grade.setPenalty(penalty);

        if (value != 0) {
            grade.setValue(value);
        }

        if (professorName != null && !professorName.isEmpty()) {
            grade.setProfessorName(professorName);
        }

        if (feedback != null) {
            grade.setFeedback(feedback);
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
            throw new CommonServiceException(String.format("Student with id %s does not exist", studentId));
        }

        Assignment assignment = assignmentRepository.findOne(assignmentId);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", assignmentId));
        }

        String gradeId = Grade.createCompositeId(studentId, assignmentId);
        Grade grade = gradeRepository.findOne(gradeId);
        if (grade == null) {
            throw new CommonServiceException(String.format("Grade with id %s does not exist", gradeId));
        }

        gradeRepository.delete(gradeId);
        
        return grade;
    }

    public List<Student> getStudentsForGroup(String group) {
        return streamFromIterable(getStudents())
                .filter(student -> student.getGroup().equals(group))
                .collect(Collectors.toList());
    }

    public List<Student> getStudentsWithAssignment(String assignmentId) {
        return streamFromIterable(getGrades())
                .filter(grade -> grade.getAssignmentId().equals(assignmentId))
                .map(Grade::getStudentId)
                .map(studentRepository::findOne)
                .collect(Collectors.toList());
    }

    public List<Student> getStudentsWithAssignmentProfessor(String assignmentId, String professorName) {
        return streamFromIterable(getGrades())
                .filter(grade -> grade.getAssignmentId().equals(assignmentId))
                .filter(grade -> grade.getProfessorName().equals(professorName))
                .map(Grade::getStudentId)
                .map(studentRepository::findOne)
                .collect(Collectors.toList());
    }

    public List<Grade> getGradesAtAssignmentInWeek(String assignmentId, long week) {
        return streamFromIterable(getGrades())
                .filter(grade -> grade.getAssignmentId().equals(assignmentId))
                .filter(grade -> {
                    try {
                        return year.getWeeksSinceStart(grade.getDate()) == week;
                    } catch (UniversityYearError universityYearError) {
                        return false;
                    }
                })
                .collect(Collectors.toList());
    }
}
