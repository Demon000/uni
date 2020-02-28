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
     * Get the number of weeks in this semester.
     * @return the number of weeks in this semester
     */
    public long getNumberOfWeeksInSemester() throws UniversityYearError {
        LocalDate today = LocalDate.now();

        try {
            firstSemester.getWeeksSinceStart(today);
            return firstSemester.getNumberOfWeeks();
        } catch (UniversitySemesterError e) {}

        try {
            secondSemester.getWeeksSinceStart(today);
            return secondSemester.getNumberOfWeeks();
        } catch (UniversitySemesterError e) {}

        throw new UniversityYearError("Date is not inside the current year");
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

//        try {
//            return secondSemester.getWeeksSinceStart(date);
//        } catch (UniversitySemesterError ignored) {}

        throw new UniversityYearError("Date is not inside the current year");
    }

    /**
     * Get the number of weeks that passed until today.
     * @return the number of weeks from the current semester that passed until today
     * @throws UniversityYearError if we are not inside the current year
     */
    public long getWeeksSinceStart() throws UniversityYearError {
        LocalDate today = LocalDate.now();
        return getWeeksSinceStart(today);
    }
}
