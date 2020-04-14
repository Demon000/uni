package utils;

public class ServiceError extends Exception {
    public ServiceError(String message) {
        super(message);
    }

    public ServiceError(Exception ex) {
        super(ex);
    }
}
