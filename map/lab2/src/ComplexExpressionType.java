public enum ComplexExpressionType {
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION,
    DIVISION;

    public static ComplexExpressionType fromString(String operator) throws Exception {
        switch (operator) {
            case "+":
                return ADDITION;
            case "-":
                return SUBSTRACTION;
            case "*":
                return MULTIPLICATION;
            case "/":
                return DIVISION;
            default:
                throw new Exception("Invalid operator string.");
        }
    }
}
