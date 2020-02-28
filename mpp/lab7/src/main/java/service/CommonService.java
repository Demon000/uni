package service;

import domain.Assignment;
import domain.Grade;
import domain.Student;
import repository.BaseRepository;
import time.UniversityYear;
import time.UniversityYearError;
import observer.Observable;
import validator.AssignmentValidator;
import validator.GradeValidator;
import validator.StudentValidator;
import validator.ValidationException;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

import static utils.CollectionUtils.listFromIterable;
import static utils.CollectionUtils.streamFromIterable;

public class CommonService extends Observable {
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
     * @param motivatedWeeks the new motivated weeks of the student, can be null to use an empty list
     * @return the newly created student
     * @throws CommonServiceException if a student with the given id already exists
     * @throws ValidationException if the student is invalid
     */
    public Student addStudent(String id, String firstName, String lastName, String email,
                              String group, String professorName, List<Long> motivatedWeeks)
            throws CommonServiceException, ValidationException {
        Student student = studentRepository.findOne(id);
        if (student != null) {
            throw new CommonServiceException(String.format("Student with id %s already exists", id));
        }

        if (motivatedWeeks == null) {
            motivatedWeeks = new ArrayList<>();
        }

        student = new Student(id, firstName, lastName, email, group, professorName, motivatedWeeks);

        studentRepository.save(student);

        change("students", null, student);
        
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
        change("students", student, student);

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
        change("students", student, student);

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
        change("students", student, student);

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
        change("students", student, null);

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
        change("assignments", null, assignment);

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
     * Get an assignment by id.
     * @param id the id of the assignment
     * @return the assignment
     * @throws CommonServiceException if the assignment does not exist
     */
    public Assignment getAssignmentById(String id) throws CommonServiceException {
        Assignment assignment = assignmentRepository.findOne(id);
        if (assignment == null) {
            throw new CommonServiceException(String.format("Assignment with id %s does not exist", id));
        }

        return assignment;
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
        change("assignments", assignment, assignment);

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
        change("assignments", assignment, null);

        return assignment;
    }

    /**
     * Get the motivated weeks which can be used to decrease the penalty of a grade.
     * @param studentId the id of the student
     * @param assignmentId the id of the assignment
     * @param date the date the assignment will be turned in, can be null to use today's date
     * @return the motivated weeks which can be used to decrease the penalty of a grade
     * @throws CommonServiceException if the student or assignment do not exist
     * @throws UniversityYearError if the given date is not part of the current semester
     */
    public List<Long> getGradeMotivatedWeeks(String studentId, String assignmentId, LocalDate date) throws CommonServiceException, UniversityYearError {
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

        List<Long> usedMotivatedWeeks = new ArrayList<>();
        long deadlineWeek = assignment.getDeadlineWeek();
        long currentWeek = year.getWeeksSinceStart(date);
        long penalty = currentWeek - deadlineWeek;

        List<Long> motivatedWeeks = student.getMotivatedWeeks();
        for (long motivatedWeek : motivatedWeeks) {
            if (penalty <= 0) {
                return usedMotivatedWeeks;
            }

            if (motivatedWeek >= deadlineWeek && motivatedWeek <= currentWeek) {
                penalty--;
                usedMotivatedWeeks.add(motivatedWeek);
            }
        }

        return usedMotivatedWeeks;
    }

    /**
     * Get the penalty that will be added for an assignment if it were to be turned in at a specific date.
     * @param studentId the id of the student
     * @param assignmentId the id of the assignment
     * @param date the date the assignment will be turned in, can be null to use today's date
     * @return the penalty that needs to be applied to the current grade
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

        long deadlineWeek = assignment.getDeadlineWeek();
        long currentWeek = year.getWeeksSinceStart(date);
        long penalty = currentWeek - deadlineWeek;

        if (penalty <= 0) {
            return 0;
        }

        List<Long> usedMotivatedWeeks = getGradeMotivatedWeeks(studentId, assignmentId, date);

        return penalty - usedMotivatedWeeks.size();
    }

    /**
     * Add a grade.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of the assignment at which the student received this grade
     * @param date the date the student received this grade on, can be null to use today's date
     * @param value the value of the grade
     * @param professorName the name of the professor that added the grade
     * @param feedback the feedback of the grade, can be null or empty to use "none"
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

        if (feedback == null || feedback.isEmpty()) {
            feedback = "none";
        }

        grade = new Grade(gradeId, date, penalty, value, professorName, feedback);

        gradeRepository.save(grade);
        change("grades", null, grade);

        return grade;
    }

    /**
     * Get all the grades.
     * @return an iterable with all the grades
     */
    public Iterable<Grade> getGrades() {
        return gradeRepository.findAll();
    }

    public Grade getGradeById(String studentId, String assignmentId) throws CommonServiceException {
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

        return grade;
    }

    /**
     * Update a grade.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of this assignment at which the student received this grade
     * @param value the new value of this grade, can be 0 to not update it
     * @param date the new date of this grade, can be null to not update it
     * @param professorName the new name of the professor that added the grade, can be null or empty to not update it
     * @param feedback the new feedback of this grade, can be null or empty to not update it
     * @return the updated grade
     * @throws CommonServiceException if the student, assignment or grade do not exist
     * @throws ValidationException if the grade is invalid
     */
    public Grade updateGrade(String studentId, String assignmentId, LocalDate date, Integer value,
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

        if (value != null) {
            grade.setValue(value);
        }

        if (professorName != null && !professorName.isEmpty()) {
            grade.setProfessorName(professorName);
        }

        if (feedback != null && !feedback.isEmpty()) {
            grade.setFeedback(feedback);
        }

        gradeRepository.update(grade);
        change("grades", grade, grade);

        return grade;
    }

    /**
     * Set a grade. If the grade exists, it is updated, if it doesn't exist, it's added.
     * @param studentId the id of the student who received this grade
     * @param assignmentId the id of the assignment at which the student received this grade
     * @param date the date the student received this grade on, can be null to use today's date
     * @param value the value of the grade
     * @param professorName the name of the professor that added the grade
     * @param feedback the feedback of the grade, can be null or empty to use "none"
     * @return the newly created grade
     */
    public Grade setGrade(String studentId, String assignmentId, LocalDate date, int value,
                          String professorName, String feedback)
            throws UniversityYearError, CommonServiceException, ValidationException {
        Grade grade = null;

        try {
            grade = getGradeById(studentId, assignmentId);
        } catch (CommonServiceException ignored) {}

        if (grade == null) {
            grade = addGrade(studentId, assignmentId, date, value, professorName, feedback);
        } else {
            grade = updateGrade(studentId, assignmentId, date, value, professorName, feedback);
        }

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
        change("grades", grade, null);

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

    public List<Grade> getGradesForStudent(String studentId) {
        return streamFromIterable(getGrades())
                .filter(grade -> grade.getStudentId().equals(studentId))
                .collect(Collectors.toList());
    }

    public double getStudentAverageGrade(String studentId) {
        Optional<Long> numberOfWeeks = streamFromIterable(getAssignments())
                .map(Assignment::getNumberOfWeeks)
                .reduce(Long::sum);

        if (numberOfWeeks.isEmpty()) {
            return 0;
        }

        Optional<Long> ponderedSum = getGradesForStudent(studentId).stream()
                .map(grade -> {
                    Assignment assignment;
                    try {
                        assignment = getAssignmentById(grade.getAssignmentId());
                    } catch (CommonServiceException e) {
                        return 0L;
                    }

                    return (grade.getValue() - grade.getPenalty()) * assignment.getNumberOfWeeks();
                })
                .reduce(Long::sum);

        if (ponderedSum.isEmpty()) {
            return 0;
        }

        return ponderedSum.get() * 1.0 / numberOfWeeks.get();
    }

    public Map<Assignment, Double> getAssignmentsAverageGrades() {
        Map<Assignment, Integer> assignmentsGradeSum = new HashMap<>();
        int numberOfStudents = listFromIterable(getStudents()).size();

        getGrades().forEach(grade -> {
            Assignment assignment;
            try {
                assignment = getAssignmentById(grade.getAssignmentId());
            } catch (CommonServiceException ignored) {
                return;
            }

            int currentSum = assignmentsGradeSum.getOrDefault(assignment, 0);
            currentSum += grade.getValue();
            assignmentsGradeSum.put(assignment, currentSum);
        });

        Map<Assignment, Double> assignmentsGradeAverage = new HashMap<>();
        for (Map.Entry<Assignment, Integer> sum : assignmentsGradeSum.entrySet()) {
            double average = 0;
            if (numberOfStudents != 0) {
                average = sum.getValue() * 1.0 /  numberOfStudents;
            }

            assignmentsGradeAverage.put(sum.getKey(), average);
        }

        return assignmentsGradeAverage;
    }

    public Assignment getLowestAverageGradeAssignment() {
        Map<Assignment, Double> assignmentsGradeAverage = getAssignmentsAverageGrades();
        Map.Entry<Assignment, Double> min = Collections.min(assignmentsGradeAverage.entrySet(), Map.Entry.comparingByValue());
        return min.getKey();
    }
}
