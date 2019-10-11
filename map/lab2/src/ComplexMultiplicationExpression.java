import java.util.Iterator;
import java.util.List;

public class ComplexMultiplicationExpression extends ComplexExpression {
    public ComplexMultiplicationExpression(List<ComplexNumber> a) {
        super(a);
    }

    @Override
    public ComplexNumber execute() {
        Iterator iterator = args.iterator();
        ComplexNumber result = (ComplexNumber) iterator.next();

        while (iterator.hasNext()) {
            ComplexNumber current = (ComplexNumber) iterator.next();
            result = ComplexNumber.multiply(result, current);
        }

        return result;
    }
}
