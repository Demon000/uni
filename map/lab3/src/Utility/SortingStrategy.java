package Utility;

public enum SortingStrategy {
    FIFO,
    LIFO;

    public static SortingStrategy fromString(String strategyName) throws Exception {
        switch (strategyName) {
            case "FIFO":
                return FIFO;
            case "LIFO":
                return LIFO;
            default:
                throw new Exception("Invalid sorting strategy.");
        }
    }
}
