package time;

import java.time.LocalDate;

public class UniversityYear {
    private final UniversitySemester firstSemester;
    private final UniversitySemester secondSemester;

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
     * @return the number of weeks in this year
     */
    public long getNumberOfWeeks() {
        return firstSemester.getNumberOfWeeks() + secondSemester.getNumberOfWeeks();
    }

    /**
     * Get the number of weeks that will pass until the given date.
     * @param date the date for which to calculate the number of weeks
     * @return the number of weeks from the current semester that will pass until the given date
     * @throws UniversityYearError if the given date is not inside the current year
     */
    public long getWeeksSinceStart(LocalDate date) throws UniversityYearError {
        try {
            return firstSemester.getWeeksSinceStart(date);
        } catch (UniversitySemesterError ignored) {}

        try {
            return secondSemester.getWeeksSinceStart(date);
        } catch (UniversitySemesterError ignored) {}

        throw new UniversityYearError("Date is not inside the current year.");
    }
}
