package time;

import utils.DateUtils;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import static utils.DateUtils.getWeeksBetweenDates;

public class DateInterval {
    private final LocalDate startDate;
    private final LocalDate endDate;

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
        return getWeeksBetweenDates(startDate, endDate);
    }

    /**
     * Get the number of weeks that will pass until the given date.
     * @param date the date for which to calculate the number of weeks that will pass.
     * @return the number of weeks that will pass until the given date,
     * -1 if the date is not inside this date interval.
     */
    public long getWeeksSinceStart(LocalDate date) throws DateIntervalError {
        final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("d/MM/yyyy");

        if (date.isBefore(startDate)) {
            throw new DateIntervalError(String.format("Date %s is before the start date %s", dateFormatter.format(date),
                    dateFormatter.format(startDate)));
        }

        if (date.isAfter(endDate)) {
            throw new DateIntervalError(String.format("Date %s is after the end date %s", dateFormatter.format(date),
                    dateFormatter.format(endDate)));
        }

        return getWeeksBetweenDates(startDate, date);
    }
}
