package Validator;

import Domain.Assignment;
import Time.UniversityYear;
import Time.UniversityYearError;

import java.time.LocalDate;

public class AssignmentValidator extends BaseStringEntityValidator<Assignment> {
    private UniversityYear year;

    public AssignmentValidator(UniversityYear year) {
        this.year = year;
    }

    /**
     * Validate an assignment description.
     * @param description the description to be validated
     * @throws ValidationException if the description isn't valid
     */
    public void validateDescription(String description) throws ValidationException {
        if (description == null) {
            throw new ValidationException("Description must not be null");
        }
        if (description.length() < 10) {
            throw new ValidationException("Description must be at least 10 characters long");
        }
    }

    /**
     * Validate the starting week and the deadline week taking into account the current week.
     * @param startWeek the starting week to be validated
     * @param deadlineWeek the deadline week to be validated
     * @throws ValidationException if the starting week or the deadline week aren't valid
     */
    public void validateWeeksRelative(long startWeek, long deadlineWeek) throws ValidationException {
        LocalDate today = LocalDate.now();
        long todayWeek;

        try {
            todayWeek = year.getWeeksSinceStart(today);
        } catch (UniversityYearError universityYearError) {
            throw new ValidationException("Current week must be inside university year");
        }

        if (startWeek < todayWeek) {
            throw new ValidationException("Start week must be after current or the same as the current week");
        }

        if (startWeek > deadlineWeek) {
            throw new ValidationException("Deadline week must be after or the same as start week");
        }
    }

    @Override
    public void validate(Assignment assignment) throws ValidationException {
        if (assignment == null) {
            throw new ValidationException("Assignment must not be null");
        }

        super.validate(assignment);

        validateDescription(assignment.getDescription());
        validateWeeksRelative(assignment.getStartWeek(), assignment.getDeadlineWeek());
    }
}
