package Time;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class UniversitySemester {
    private List<DateInterval> intervals = new ArrayList<DateInterval>();

    /**
     * Add an interval to this semester.
     * @param di the interval to add
     */
    public void addInterval(DateInterval di) {
        intervals.add(di);
    }

    /**
     * Add a DateInterval to this semester formed using the given start and end dates.
     * @param startDate the start date of the interval (including)
     * @param endDate the end date of the interval (including)
     * @throws DateIntervalError if the end date is before the start date
     */
    public void addIntervalFromLocalDates(LocalDate startDate, LocalDate endDate) throws DateIntervalError {
        DateInterval interval = new DateInterval(startDate, endDate);
        addInterval(interval);
    }

    /**
     * Get the number of weeks in this semester.
     * @return the number of weeks in this semester
     */
    public long getNumberOfWeeks() {
        int numberOfWeeks = 0;
        for (DateInterval interval : intervals) {
            numberOfWeeks += interval.getNumberOfWeeks();
        }

        return numberOfWeeks;
    }

    /**
     * Get the number of weeks that will pass until the given date.
     * @param date the date for which to calculate the number of weeks
     * @return the number of weeks from this semester that will pass until the given date,
     * -1 if the date is not within this semester
     */
    public long getWeeksSinceStart(LocalDate date) {
        int numberOfWeeks = 0;
        for (DateInterval interval : intervals) {
            if (interval.isInside(date)) {
                return numberOfWeeks + interval.getWeeksSinceStart(date);
            }

            numberOfWeeks += interval.getNumberOfWeeks();
        }

        return -1;
    }

    /**
     * Find whether if the given date is inside this semester.
     * @param date the date for which to find
     * @return whether the date is inside this semester
     */
    public boolean isInside(LocalDate date) {
        return getWeeksSinceStart(date) != -1;
    }

    /**
     * Create a semester from an even list of given dates
     * @param dates an even list of given dates
     * @return the semester created from the given dates
     * @throws UniversitySemesterError if the given dates list is not even
     * @throws DateIntervalError if an even date comes before an uneven date
     */
    public static UniversitySemester fromLocalDates(LocalDate ... dates) throws UniversitySemesterError, DateIntervalError {
        UniversitySemester semester = new UniversitySemester();

        if (dates.length % 2 != 0) {
            throw new UniversitySemesterError("Local dates must come in pairs of 2 to form date intervals");
        }

        for (int i = 0; i < dates.length; i += 2) {
            semester.addIntervalFromLocalDates(dates[i], dates[i + 1]);
        }

        return semester;
    }
}
