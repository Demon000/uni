import java.util.regex.*;

public class ComplexNumber {
    private double real;
    private double imaginary;

    public ComplexNumber(double r, double i) {
        real = r;
        imaginary = i;
    }

    public static ComplexNumber add(ComplexNumber first, ComplexNumber second) {
        double r = first.real + second.real;
        double i = first.imaginary + second.imaginary;

        return new ComplexNumber(r, i);
    }

    public static ComplexNumber substract(ComplexNumber first, ComplexNumber second) {
        double r = first.real - second.real;
        double i = first.imaginary - second.imaginary;

        return new ComplexNumber(r, i);
    }

    public static ComplexNumber multiply(ComplexNumber first, ComplexNumber second) {
        double r = first.real * second.real - first.imaginary * second.imaginary;
        double i = first.real * second.imaginary + first.imaginary * second.real;

        return new ComplexNumber(r, i);
    }

    public static ComplexNumber divide(ComplexNumber first, ComplexNumber second) {
        double divider = Math.pow(second.real, 2) + Math.pow(second.imaginary, 2);
        double r = (first.real * second.real + first.imaginary * second.imaginary) / divider;
        double i = (first.imaginary * second.real - first.real * second.imaginary) / divider;

        return new ComplexNumber(r, i);
    }

    private static void appendGroup(StringBuilder builder, Matcher matcher, String name) {
        String group = matcher.group(name);
        if (group != null) {
            builder.append(group);
        }
    }

    private static void appendGroups(StringBuilder builder, Matcher matcher, String[] names) {
        for (String name : names) {
            appendGroup(builder, matcher, name);
        }
    }

    public static ComplexNumber fromString(String expression) throws Exception {
        final Pattern pattern = Pattern.compile("(?<realSign>\\+|\\-)?(?<realDecimalPart>\\d+)(?<realFractionalPart>\\.\\d+)?" +
                "(?<imaginarySign>\\+|\\-)(?<imaginaryDecimalPart>\\d+)(?<imaginaryFractionalPart>\\.\\d+)?(\\*i)");
        Matcher matcher = pattern.matcher(expression);

        if (!matcher.matches()) {
            throw new Exception("Invalid complex number expression.");
        }

        final String[] realGroups = new String[]{"realSign", "realDecimalPart", "realFractionalPart"};
        StringBuilder realBuilder = new StringBuilder();
        appendGroups(realBuilder, matcher, realGroups);
        double r = Double.parseDouble(realBuilder.toString());

        final String[] imaginaryGroups = new String[]{"imaginarySign", "imaginaryDecimalPart", "imaginaryFractionalPart"};
        StringBuilder imaginaryBuilder = new StringBuilder();
        appendGroups(imaginaryBuilder, matcher, imaginaryGroups);
        double i = Double.parseDouble(imaginaryBuilder.toString());

        System.out.println(r);
        System.out.println(i);

        return new ComplexNumber(r, i);
    }
}
