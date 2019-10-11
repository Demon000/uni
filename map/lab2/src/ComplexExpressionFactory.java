import java.util.List;

public class ComplexExpressionFactory {
    public static ComplexExpression createFromType(ComplexExpressionType expressionType, List<ComplexNumber> args) throws Exception {
        switch (expressionType) {
            case ADDITION:
                return new ComplexAdditionExpression(args);
            case SUBTRACTION:
                return new ComplexSubstractionExpression(args);
            case MULTIPLICATION:
                return new ComplexMultiplicationExpression(args);
            case DIVISION:
                return new ComplexDivisionExpression(args);
            default:
                throw new Exception("Invalid expression type.");
        }
    }
}
