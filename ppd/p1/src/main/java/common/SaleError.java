package common;

public class SaleError extends Throwable {
    public String message;

    public SaleError(String message) {
        this.message = message;
    }

    @Override
    public String toString() {
        return "SaleError{" +
                "message='" + message + '\'' +
                '}';
    }
}
