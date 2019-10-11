import java.util.Iterator;
import java.util.List;

public class ComplexSubstractionExpression extends ComplexExpression {
    public ComplexSubstractionExpression(List<ComplexNumber> a) {
        super(a);
    }

    @Override
    public ComplexNumber execute() {
        Iterator iterator = args.iterator();
        ComplexNumber result = (ComplexNumber) iterator.next();

        while (iterator.hasNext()) {
            ComplexNumber current = (ComplexNumber) iterator.next();
            result = ComplexNumber.subtract(result, current);
        }

        return result;
    }
}
