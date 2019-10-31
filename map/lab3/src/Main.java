import Tests.Tests;

public class Main {
    public static void main(String[] argc) {
        String strategyName = "FIFO";
        if (argc.length > 0) {
            strategyName = argc[0];
        }

        Tests tests = new Tests(strategyName);
        tests.testAll();
    }
}
