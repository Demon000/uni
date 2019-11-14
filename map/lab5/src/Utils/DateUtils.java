package Utils;

import java.time.LocalDate;
import java.time.temporal.TemporalField;
import java.time.temporal.WeekFields;
import java.util.Locale;

import static java.time.temporal.ChronoUnit.DAYS;

public class DateUtils {
    private final static TemporalField dayField = WeekFields.of(Locale.getDefault()).dayOfWeek();

    public static long getWeeksBetweenDates(LocalDate first, LocalDate second) {
        /* Make sure the first date is a Monday and the end date is the next Monday */
        LocalDate startDate = first.with(dayField, 1);
        LocalDate exclusiveEndDate = second.with(dayField, 7).plusDays(1);

        long numberOfDays = DAYS.between(startDate, exclusiveEndDate);
        return numberOfDays / 7;
    }
}
