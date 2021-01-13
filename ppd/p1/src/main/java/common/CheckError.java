package common;

public class CheckError extends Throwable {
    public String message;

    public CheckError(String message) {
        this.message = message;
    }
}
