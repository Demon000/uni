import IUser from '../../common/domain/IUser';
import ISafeUser from '../../common/domain/ISafeUser';

export default class User implements IUser {
    id: number;
    username: string;
    password: string;

    constructor(options: IUser) {
        this.id = options?.id;
        this.username = options?.username;
        this.password = options?.password;
    }

    toPasswordSafe(): ISafeUser {
        return {
            id: this.id,
            username: this.username,
        };
    }
}
