package repository;

import com.fasterxml.jackson.annotation.JsonAutoDetect;

import java.io.Serializable;

public class RepositoryError extends Exception {
    RepositoryError(String message) {
        super(message);
    }

    public RepositoryError(Exception ex) {
        super(ex);
    }

    public Document getDocument() {
        return new Document(this.getMessage());
    }

    public class Document implements Serializable {
        private final boolean error = true;
        private final String message;

        private Document(String message) {
            this.message = message;
        }


        public boolean isError() {
            return error;
        }

        public String getMessage() {
            return message;
        }
    }
}
