public class Main {
    public static void main(String[] args) {
        try {
            PPDUtils.writeRandomNumbersToFile("test.txt", 30, 1, 10);
            int result = PPDUtils.compareNumbersFromFile("first.txt", "second.txt");
            System.out.printf("first.txt vs second.txt: %d\n", result);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
