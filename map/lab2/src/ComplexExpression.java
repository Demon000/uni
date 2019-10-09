public abstract class ComplexExpression {
    private ComplexExpressionType type;
    private ComplexNumber[] args;

    public ComplexExpression(ComplexExpressionType t, ComplexNumber[] a) {
        type = t;
        args = a;
    }

    public abstract ComplexNumber execute();
}
