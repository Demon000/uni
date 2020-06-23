import User, {UserOptions} from '../domain/User';
import IUserRepository from '../repository/IUserRepository';
import {LoginError, UserNotFoundError} from '../lib/Errors';

export default class UserService {
    private _repository: IUserRepository;

    constructor(repository: IUserRepository) {
        this._repository = repository;
    }

    async createUser(options: UserOptions): Promise<User> {
        const user = new User(options);
        await this._repository.add(user);
        return user;
    }

    async getUserById(id: number) {
        const user = await this._repository.findOneById(id);
        if (!user) {
            throw new UserNotFoundError();
        }

        return user;
    }

    async getUserByUsername(username: string) {
        const user = await this._repository.findOneByUsername(username);
        if (!user) {
            throw new UserNotFoundError();
        }

        return user;
    }

    async verifyPassword(user: User, password: string) {
        if (!password) {
            throw new LoginError();
        }

        const isCorrect = await this._repository.verifyPassword(user, password);
        if (!isCorrect) {
            throw new LoginError();
        }
    }

    async createTestUsers(testUsersConfig: [User]) {
        for (const userConfig of testUsersConfig) {
            try {
                await this.createUser(userConfig);
            } catch (e) {
                console.error(e);
                console.log(`Already added test user ${userConfig.username}`);
            }
        }
    }
}
