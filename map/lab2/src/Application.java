import java.beans.Expression;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Application {
    private static ComplexExpressionType getExpressionType(List<ComplexExpressionType> expressionTypes) throws Exception {
        Iterator iterator = expressionTypes.iterator();
        ComplexExpressionType first = (ComplexExpressionType) iterator.next();

        while (iterator.hasNext()) {
            ComplexExpressionType current = (ComplexExpressionType) iterator.next();
            if (current != first) {
                throw new Exception("Expressions are not of the same type.");
            }
        }

        return first;
    }
    public static void main(String[] args) {
        int argsLength = args.length;
        List<ComplexNumber> numbers = new ArrayList<ComplexNumber>();
        List<ComplexExpressionType> expressionTypes = new ArrayList<ComplexExpressionType>();

        for (int i = 0; i < argsLength; i++) {
            if (i % 2 == 0) {
                ComplexNumber number;

                try {
                    number = ComplexNumber.fromString(args[i]);
                } catch (Exception e) {
                    System.out.println(e.toString());
                    return;
                }
                numbers.add(number);
            } else {
                ComplexExpressionType expressionType;
                try {
                    expressionType = ComplexExpressionType.fromString(args[i]);
                } catch (Exception e) {
                    System.out.println(e.toString());
                    return;
                }
                expressionTypes.add(expressionType);
            }
        }

        ComplexExpressionType expressionType;
        try {
            expressionType = getExpressionType(expressionTypes);
        } catch (Exception e) {
            System.out.println(e.toString());
            return;
        }

        ComplexExpression expression = null;
        try {
            expression = ComplexExpressionFactory.createFromType(expressionType, numbers);
        } catch (Exception e) {
            System.out.println(e.toString());
            return;
        }
        ComplexNumber result = expression.execute();
        System.out.println(result.toString());
    }
}
