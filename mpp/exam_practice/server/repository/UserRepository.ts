import IUserRepository from './IUserRepository';
import User from '../../common/domain/User';
import {EntityRepository, Repository} from 'typeorm';

@EntityRepository(User)
export default class UserRepository extends Repository<User> implements IUserRepository {
    async add(user: User): Promise<void> {
        await this.save(user);
    }

    async findOneById(id: number): Promise<User | undefined> {
        return await this.findOne({
            id,
        });
    }

    async findOneByUsername(username: string): Promise<User | undefined> {
        return await this.findOne({
            username,
        });
    }

    async verifyPassword(user: User, password: string): Promise<boolean> {
        return user.password === password;
    }
}
