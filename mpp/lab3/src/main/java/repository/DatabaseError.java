package repository;

public class DatabaseError extends RepositoryError {
    public DatabaseError(String message) {
        super(message);
    }

    public DatabaseError(Throwable cause) {
        super(cause);
    }
}
