import User from '../domain/User';

export default interface IUserRepository {
    add(user: User): Promise<void>;
    findOneById(id: number): Promise<User | undefined>;
    findOneByUsername(username: string): Promise<User | undefined>;
    verifyPassword(user: User, password: string): Promise<boolean>;
}
