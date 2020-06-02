const Config = require('config');
const TestUsersConfig = Config.get('TestUsers');

const User = require('../models/User');
const Errors = require('../lib/Errors');

class UserService {
    static async createUser(data) {
        const user = new User(data);
        await user.save();
        return user;
    }

    static getUsers() {
        return User.find().exec();
    }

    static async getUserByUserName(username) {
        const user = await User.findByUsername(username);
        if (!user) {
            throw new Errors.UserNotFoundError();
        }

        return user;
    }

    static async verifyPassword(user, password) {
        if (!password) {
            throw new Errors.LoginError();
        }

        const isCorrect = await user.verifyPassword(password);
        if (!isCorrect) {
            throw new Errors.LoginError();
        }
    }

    static async createTestUsers() {
        console.log('Adding test users.');
        for (const role in TestUsersConfig) {
            const users = TestUsersConfig[role];
            for (const user of users) {
                const data = Object.assign({role}, user);
                try {
                    await this.createUser(data);
                } catch (e) {
                    console.log(`Already added test user ${user.username} with role ${role}.`);
                }
            }
        }
    }
}

module.exports = UserService;
