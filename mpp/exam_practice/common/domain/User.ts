export interface UserOptions {
    id: number;
    username: string;
    password: string;
}

export default class User {
    id: number;
    username: string;
    password: string;

    constructor(options: UserOptions) {
        this.id = options?.id;
        this.username = options?.username;
        this.password = options?.password;
    }

    toResponse(): object {
        return {
            id: this.id,
            username: this.username,
        };
    }
}
