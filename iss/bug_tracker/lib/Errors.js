class CustomError extends Error {
    constructor(status, code, message) {
        super(message);
        this.code = code;
        this.status = status;
    }
}

class HelloError extends CustomError {
    constructor() {
        super(400, 'hello-error', 'Hello error.');
    }
}

class UserCreateError extends CustomError {
    constructor() {
        super(400, 'user-create-error', 'Failed to create user.');
    }
}

class LoginError extends CustomError {
    constructor() {
        super(401, 'login-error', 'Login failed.');
    }
}

class AccessTokenError extends CustomError {
    constructor() {
        super(401, 'access-token-error', 'Access token is invalid.');
    }
}

class UserNotFoundError extends CustomError {
    constructor() {
        super(404, 'user-not-found-error', 'User not found.');
    }
}

class UserForbiddenError extends CustomError {
    constructor() {
        super(403, 'user-forbidden', 'User is not allowed to access resource.');
    }
}

class BugNotFoundError extends CustomError {
    constructor() {
        super(404, 'bug-not-found', 'Bug not found.');
    }
}

class AlreadySubscribedError extends CustomError {
    constructor() {
        super(403, 'already-subscribed-error', 'User is already subscribed to bug events.');
    }
}

module.exports = {
    HelloError,
    UserCreateError,
    LoginError,
    AccessTokenError,
    UserNotFoundError,
    UserForbiddenError,
    BugNotFoundError,
    AlreadySubscribedError,
};
