package utils;

import org.junit.Test;

import java.time.LocalDate;

import static org.junit.Assert.*;

public class DateUtilsTest {

    @Test
    public void getWeeksBetweenDates() {
        LocalDate now = LocalDate.now();
        LocalDate nextWeek = LocalDate.now().plusWeeks(1);
        assertEquals(1, DateUtils.getWeeksBetweenDates(now, now));
        assertEquals(2, DateUtils.getWeeksBetweenDates(now, nextWeek));
    }
}