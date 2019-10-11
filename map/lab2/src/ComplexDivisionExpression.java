import java.util.Iterator;
import java.util.List;

public class ComplexDivisionExpression extends ComplexExpression {
    public ComplexDivisionExpression(List<ComplexNumber> a) {
        super(a);
    }

    @Override
    public ComplexNumber execute() {
        Iterator iterator = args.iterator();
        ComplexNumber result = (ComplexNumber) iterator.next();

        while (iterator.hasNext()) {
            ComplexNumber current = (ComplexNumber) iterator.next();
            result = ComplexNumber.divide(result, current);
        }

        return result;
    }
}
