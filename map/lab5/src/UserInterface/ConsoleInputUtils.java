package UserInterface;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Scanner;

public class ConsoleInputUtils {
    public static String readString() {
        Scanner input = new Scanner(System.in);
        return input.nextLine().strip();
    }

    public static String readString(String message) {
        System.out.print(message);
        return readString();
    }

    public static String readString(String message, String errorMessage) {
        while (true) {
            String result = readString(message);
            if (result != null && !result.isEmpty()) {
                return result;
            }

            System.out.println(errorMessage);
        }
    }

    public static int readNatural() {
        String result = readString();
        return Integer.parseInt(result);
    }

    public static int readNatural(String message) {
        try {
            System.out.print(message);
            return readNatural();
        } catch (Exception e) {
            return -1;
        }
    }

    public static int readNatural(String message, String errorMessage) {
        while (true) {
            int result = readNatural(message);
            if (result != -1) {
                return result;
            }

            System.out.println(errorMessage);
        }
    }

    public static LocalDate readDate() {
        DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        String result = readString();
        return LocalDate.parse(result, dateFormatter);
    }

    public static LocalDate readDate(String message) {
        try {
            System.out.print(message);
            return readDate();
        } catch (Exception e) {
            return null;
        }
    }

    public static LocalDate readDate(String message, String errorMessage) {
        while (true) {
            LocalDate result = readDate(message);
            if (result != null) {
                return result;
            }

            System.out.println(errorMessage);
        }
    }
}
