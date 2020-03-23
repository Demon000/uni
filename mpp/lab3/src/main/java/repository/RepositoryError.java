package repository;

public class RepositoryError extends Exception {
    public RepositoryError(String message) {
        super(message);
    }

    public RepositoryError(Throwable cause) {
        super(cause);
    }
}
