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
