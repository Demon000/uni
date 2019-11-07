package Time;

import java.time.LocalDate;

public class UniversityYear {
    private UniversitySemester firstSemester;
    private UniversitySemester secondSemester;

    /**
     * Create an university year.
     * @param fs the first semester of the year
     * @param ss the second semester of the year
     */
    public UniversityYear(UniversitySemester fs, UniversitySemester ss) {
        firstSemester = fs;
        secondSemester = ss;
    }

    /**
     * Get the number of weeks in this year.
     * @return
     */
    public long getNumberOfWeeks() {
        return firstSemester.getNumberOfWeeks() + secondSemester.getNumberOfWeeks();
    }

    /**
     * Get the number of weeks that will pass until the given date.
     * @param date the date for which to calculate the number of weeks
     * @return the number of weeks that will pass until the given date,
     * -1 if the date is not inside this year.
     */
    public long getWeeksSinceStart(LocalDate date) {
        if (firstSemester.isInside(date)) {
            return firstSemester.getWeeksSinceStart(date);
        }

        if (secondSemester.isInside(date)) {
            return secondSemester.getWeeksSinceStart(date);
        }

        return -1;
    }

    /**
     * Find whether the given date is inside this year.
     * @param date the year for which to find
     * @return whether the given date is inside this year
     */
    public boolean isInside(LocalDate date) {
        return getWeeksSinceStart(date) != -1;
    }
}
