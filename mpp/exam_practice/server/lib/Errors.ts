export class CustomError extends Error {
    private status: Number;
    private code: String;

    constructor(status: Number, code: string, message: string) {
        super(message);
        this.code = code;
        this.status = status;
    }
}

export class HelloError extends CustomError {
    constructor() {
        super(400, 'hello-error', 'Hello error.');
    }
}

export class UserNotFoundError extends CustomError {
    constructor() {
        super(404, 'user-not-found-error', 'User not found.');
    }
}

export class LoginError extends CustomError {
    constructor() {
        super(401, 'login-error', 'Login failed.');
    }
}

export class AccessTokenError extends CustomError {
    constructor() {
        super(401, 'access-token-error', 'Access token is invalid.');
    }
}

export class AlreadyPlayingError extends CustomError {
    constructor() {
        super(400, 'already-playing-error', 'Player is already playing a base-game.');
    }
}

export class NotPlayingError extends CustomError {
    constructor() {
        super(400, 'not-playing-error', 'Player is not currently playing a base-game.');
    }
}

export class QuestionNotFoundError extends CustomError {
    constructor() {
        super(400, 'question-not-found-error', 'Player tried to answer an invalid question.');
    }
}
