public class Application {
    public static void main(String[] args) {
        ComplexNumber number;
        try {
            number = ComplexNumber.fromString("2+3*i");
            number = ComplexNumber.fromString("2-3*i");
            number = ComplexNumber.fromString("-2+3*i");
            number = ComplexNumber.fromString("-2-3*i");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
