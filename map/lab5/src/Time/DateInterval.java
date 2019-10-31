package Time;

import java.time.LocalDate;
import java.time.temporal.TemporalField;
import java.time.temporal.WeekFields;
import java.util.Locale;

import static java.time.temporal.ChronoUnit.DAYS;

public class DateInterval {
    private LocalDate startDate;
    private LocalDate endDate;

    public DateInterval(LocalDate sd, LocalDate ed) throws DateIntervalError {
        startDate = sd;
        endDate = ed;

        if (sd.isAfter(ed)) {
            throw new DateIntervalError("Start date cannot be after end date");
        }
    }

    public long getNumberOfWeeks() {
        return Utils.getWeeksBetweenDates(startDate, endDate);
    }

    public long getWeeksSinceStart(LocalDate date) {
        if (date.isBefore(startDate)) {
            return -1;
        }

        if (date.isAfter(endDate)) {
            return -1;
        }

        return Utils.getWeeksBetweenDates(startDate, date);
    }

    public boolean isInside(LocalDate date) {
        return getWeeksSinceStart(date) != -1;
    }
}
