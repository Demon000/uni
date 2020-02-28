package validator;

import domain.Assignment;
import time.UniversityYear;
import time.UniversityYearError;

public class AssignmentValidator extends BaseStringEntityValidator<Assignment> {
    private final UniversityYear year;

    public AssignmentValidator(UniversityYear year) {
        this.year = year;
    }

    /**
     * Validate an id.
     * @param id the id to be validated.
     * @throws ValidationException if the id isn't valid
     */
    @Override
    public void validateId(String id) throws ValidationException {
        validateSimpleId(id);
    }

    /**
     * Validate an assignment description.
     * @param description the description to be validated
     * @throws ValidationException if the description isn't valid
     */
    public void validateDescription(String description) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> description == null,
                new ValidationException("Description must not be null"));
        exception.throwIfNotEmpty();

        exception.addExceptionIf(() -> description.length() < 10,
                new ValidationException("Description must be at least 10 characters long"));
        exception.throwIfNotEmpty();
    }

    /**
     * Validate the starting week and the deadline week taking into account the current week.
     * @param startWeek the starting week to be validated
     * @param deadlineWeek the deadline week to be validated
     * @throws ValidationException if the starting week or the deadline week aren't valid
     */
    public void validateWeeksRelative(long startWeek, long deadlineWeek) throws ValidationException {
        ValidationException exception = new ValidationException();
        long todayWeek = 0;

        try {
            todayWeek = year.getWeeksSinceStart();
        } catch (UniversityYearError universityYearError) {
            exception.addException(new ValidationException("Current week must be inside the university year"));
        }
        exception.throwIfNotEmpty();

        try {
            if (startWeek > year.getNumberOfWeeksInSemester()) {
                exception.addException(new ValidationException("Start week must be inside the university year"));
            }
        } catch (UniversityYearError universityYearError) {
            exception.addException(new ValidationException("Current week must be inside the university year"));
        }

        try {
            if (deadlineWeek > year.getNumberOfWeeksInSemester()) {
                exception.addException(new ValidationException("Deadline week must be inside the university year"));
            }
        } catch (UniversityYearError universityYearError) {
            exception.addException(new ValidationException("Current week must be inside the university year"));
        }

        long finalTodayWeek = todayWeek;
        exception.addExceptionIf(() -> startWeek < finalTodayWeek,
                new ValidationException("Start week must be after current or the same as the current week"));

        exception.addExceptionIf(() -> startWeek > deadlineWeek,
                new ValidationException("Deadline week must be after or the same as start week"));

        exception.throwIfNotEmpty();
    }

    @Override
    public void validate(Assignment assignment) throws ValidationException {
        ValidationException exception = new ValidationException();

        exception.addExceptionIf(() -> assignment == null,
                new ValidationException("Assignment must not be null"));
        exception.throwIfNotEmpty();

        exception.addExceptionIfThrown(() -> super.validate(assignment));
        exception.addExceptionIfThrown(() -> validateDescription(assignment.getDescription()));
        exception.addExceptionIfThrown(() -> validateWeeksRelative(assignment.getStartWeek(), assignment.getDeadlineWeek()));

        exception.throwIfNotEmpty();
    }
}
