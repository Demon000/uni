package service;

public class CanStartError extends Exception {

    public CanStartError(String message) {
        super(message);
    }

    public CanStartError(Exception ex) {
        super(ex);
    }
}
