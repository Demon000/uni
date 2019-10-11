import java.util.List;

public abstract class ComplexExpression {
    protected List<ComplexNumber> args;

    public ComplexExpression(List<ComplexNumber> a) {
        args = a;
    }

    public abstract ComplexNumber execute();
}
