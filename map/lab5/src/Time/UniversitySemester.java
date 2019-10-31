package Time;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class UniversitySemester {
    private List<DateInterval> intervals = new ArrayList<DateInterval>();

    public UniversitySemester() {
    }

    public void addInterval(DateInterval di) {
        intervals.add(di);
    }

    public void addIntervalFromLocalDates(LocalDate startDate, LocalDate endDate) throws DateIntervalError {
        DateInterval interval = new DateInterval(startDate, endDate);
        addInterval(interval);
    }

    public long getNumberOfWeeks() {
        int numberOfWeeks = 0;
        for (DateInterval interval : intervals) {
            numberOfWeeks += interval.getNumberOfWeeks();
        }

        return numberOfWeeks;
    }

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

    public boolean isInside(LocalDate date) {
        return getWeeksSinceStart(date) != -1;
    }

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
