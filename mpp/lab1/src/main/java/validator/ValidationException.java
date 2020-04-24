package validator;

import java.util.ArrayList;
import java.util.List;

public class ValidationException extends Exception {
    private final List<Exception> exceptions = new ArrayList<>();

    public ValidationException(String message) {
        Exception exception = new Exception(message);
        addException(exception);
    }

    public ValidationException() {
    }

    public void addException(Exception exception) {
        exceptions.add(exception);
    }

    public void addExceptionIfThrown(ValidationExceptionCallable callable) {
        try {
            callable.call();
        } catch (Exception e) {
            addException(e);
        }
    }

    public void addExceptionIf(ValidationExceptionBooleanCallable callable, Exception e) {
        if (callable.call()) {
            addException(e);
        }
    }

    public void throwIfNotEmpty() throws ValidationException {
        if (exceptions.isEmpty()) {
            return;
        }

        throw this;
    }

    @Override
    public String getMessage() {
        StringBuilder sb = new StringBuilder();

        for (Exception exception : exceptions) {
            sb.append(exception.getMessage());
            sb.append("\n");
        }

        return sb.toString();
    }
}
