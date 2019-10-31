package Time;

import java.time.LocalDate;

public class UniversityYear {
    private UniversitySemester firstSemester;
    private UniversitySemester secondSemester;

    public UniversityYear(UniversitySemester fs, UniversitySemester ss) {
        firstSemester = fs;
        secondSemester = ss;
    }

    public long getNumberOfWeeks() {
        return firstSemester.getNumberOfWeeks() + secondSemester.getNumberOfWeeks();
    }

    public long getWeeksSinceStart(LocalDate date) {
        if (firstSemester.isInside(date)) {
            return firstSemester.getWeeksSinceStart(date);
        }

        if (secondSemester.isInside(date)) {
            return secondSemester.getWeeksSinceStart(date);
        }

        return -1;
    }

    public boolean isInside(LocalDate date) {
        return getWeeksSinceStart(date) != -1;
    }
}
