package repository;

public class RepositoryError extends Exception {
    RepositoryError(String message) {
        super(message);
    }

    public RepositoryError(Exception ex) {
        super(ex);
    }
}
