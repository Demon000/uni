import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public class Utils {
    public static int generateRandomInt(int min, int max) {
        return ThreadLocalRandom.current().nextInt(min, max);
    }

    public static void writeRandomNumbersToFile(String path, int size, int min, int max) throws FileNotFoundException {
        PrintWriter output = new PrintWriter(new File(path));
        new Random().ints(size, min, max).mapToObj(String::valueOf).forEach(output::println);
        output.close();
    }

    public static int compareNumbersFromFile(String first, String second) throws Exception {
        FileReader firstReader = new FileReader(first);
        FileReader secondReader = new FileReader(second);
        Scanner firstScanner = new Scanner(firstReader);
        Scanner secondScanner = new Scanner(secondReader);
        int result;
        double firstValue;
        double secondValue;

        while (firstScanner.hasNext()) {
            if (!secondScanner.hasNext()) {
                return 1;
            }

            if (!firstScanner.hasNextDouble()
                    || !secondScanner.hasNextDouble()) {
                throw new Exception("File contains invalid data");
            }

            firstValue = firstScanner.nextDouble();
            secondValue = secondScanner.nextDouble();
            result = Double.compare(firstValue, secondValue);
            if (result != 0) {
                return result;
            }
        }

        if (secondScanner.hasNext()) {
            return -1;
        }

        return 0;

    }
}
