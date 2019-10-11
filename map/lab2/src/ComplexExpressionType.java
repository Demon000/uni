public enum ComplexExpressionType {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION;

    public static ComplexExpressionType fromString(String operator) throws Exception {
        switch (operator) {
            case "+":
                return ADDITION;
            case "-":
                return SUBTRACTION;
            case "*":
                return MULTIPLICATION;
            case "/":
                return DIVISION;
            default:
                throw new Exception("Invalid operator string.");
        }
    }
}
