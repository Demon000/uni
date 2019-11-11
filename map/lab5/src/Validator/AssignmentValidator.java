package Validator;

import Domain.Assignment;
import Time.UniversityYear;

import java.time.LocalDate;

public class AssignmentValidator extends BaseEntityStringValidator<Assignment> {
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
            throw new ValidationException("Description cannot be null");
        }
        if (description.length() < 10) {
            throw new ValidationException("Given string is too short for a description");
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
        long todayWeek = year.getWeeksSinceStart(today);

        if (startWeek > deadlineWeek) {
            throw new ValidationException("Start week is after deadline week");
        }

        if (startWeek < todayWeek) {
            throw new ValidationException("Start week is before current week");
        }
    }

    @Override
    public void validate(Assignment assignment) throws ValidationException {
        if (assignment == null) {
            throw new ValidationException("Assignment cannot be null");
        }

        super.validate(assignment);

        validateDescription(assignment.getDescription());
        validateWeeksRelative(assignment.getStartWeek(), assignment.getDeadlineWeek());
    }
}
