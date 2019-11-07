package Time;

import java.time.LocalDate;

public class DateInterval {
    private LocalDate startDate;
    private LocalDate endDate;

    /**
     * Create a date interval.
     * @param sd the start of the date interval
     * @param ed the end of the date interval
     * @throws DateIntervalError if the start date is after the end date
     */
    public DateInterval(LocalDate sd, LocalDate ed) throws DateIntervalError {
        startDate = sd;
        endDate = ed;

        if (sd.isAfter(ed)) {
            throw new DateIntervalError("Start date cannot be after end date");
        }
    }

    /**
     * Get the number of weeks inside this date interval.
     * @return the number of weeks inside this date interval
     */
    public long getNumberOfWeeks() {
        return Utils.getWeeksBetweenDates(startDate, endDate);
    }

    /**
     * Get the number of weeks that will pass until the given date.
     * @param date the date for which to calculate the number of weeks that will pass.
     * @return the number of weeks that will pass until the given date,
     * -1 if the date is not inside this date interval.
     */
    public long getWeeksSinceStart(LocalDate date) {
        if (date.isBefore(startDate)) {
            return -1;
        }

        if (date.isAfter(endDate)) {
            return -1;
        }

        return Utils.getWeeksBetweenDates(startDate, date);
    }

    /**
     * Find whether the given date is inside this date interval.
     * @param date the date for which to find
     * @return whether the given date is inside this date interval
     */
    public boolean isInside(LocalDate date) {
        return getWeeksSinceStart(date) != -1;
    }
}
