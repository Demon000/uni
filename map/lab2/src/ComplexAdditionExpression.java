import java.util.Iterator;
import java.util.List;

public class ComplexAdditionExpression extends ComplexExpression {
    public ComplexAdditionExpression(List<ComplexNumber> a) {
        super(a);
    }

    @Override
    public ComplexNumber execute() {
        Iterator iterator = args.iterator();
        ComplexNumber result = (ComplexNumber) iterator.next();

        while (iterator.hasNext()) {
            ComplexNumber current = (ComplexNumber) iterator.next();
            result = ComplexNumber.add(result, current);
        }

        return result;
    }
}
