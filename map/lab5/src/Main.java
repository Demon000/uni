import Time.DateInterval;
import Time.DateIntervalError;
import Time.UniversitySemester;
import Time.UniversityYear;

import java.time.LocalDate;

public class Main {

    public static void main(String[] args) {
        UniversitySemester firstSemester;
        UniversitySemester secondSemester;

        try {
            firstSemester = UniversitySemester.fromLocalDates(
                    LocalDate.of(2019, 9, 30), LocalDate.of(2019, 12, 20),
                    LocalDate.of(2020, 1, 6), LocalDate.of(2020, 1, 17)
            );

            secondSemester = UniversitySemester.fromLocalDates(
                    LocalDate.of(2020, 2, 24), LocalDate.of(2020, 4, 17),
                    LocalDate.of(2020, 4, 27), LocalDate.of(2020, 6, 5)
            );
        } catch (Exception e) {
            e.printStackTrace();
            return;
        }

        UniversityYear year = new UniversityYear(firstSemester, secondSemester);

        System.out.println(firstSemester.getNumberOfWeeks());
        System.out.println(secondSemester.getNumberOfWeeks());

        System.out.println(firstSemester.getWeeksSinceStart(LocalDate.of(2019, 9, 30)));
        System.out.println(firstSemester.getWeeksSinceStart(LocalDate.of(2019, 10, 13)));

        System.out.println(year.getNumberOfWeeks());
        System.out.println(year.getWeeksSinceStart(LocalDate.of(2019, 12, 21)));
    }
}
