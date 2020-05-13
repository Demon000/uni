package service;

import grpc.triathlon.ErrorNumber;

public class ServiceError extends Exception {
    ErrorNumber errorNumber;

    public ServiceError(Exception e) {
        super(e);
    }

    public ServiceError(ErrorNumber errorNumber) {
        super("Unrecognized error");

        this.errorNumber = errorNumber;
    }

    @Override
    public String getMessage() {
        switch (errorNumber) {
            case INVALID_LOGIN:
                return "Invalid login";
            case BEARER_MISSING:
                return "Bearer missing";
            case BEARER_INVALID:
                return "Bearer invalid";
            case BEARER_NOT_AUTHORIZED:
                return "Bearer not authorized";
            case ALREADY_LOGGED_IN:
                return "Client already logged in";
            case CONNECTION_ERROR:
                return "Connection error";
            case UNRECOGNIZED:
                break;
        }

        return super.getMessage();
    }
}
