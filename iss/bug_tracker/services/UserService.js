const User = require('../models/User');
const Errors = require('../lib/Errors');

class UserService {
    static async createUser(data) {
        const user = new User(data);
        await user.save();
        return user;
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
}

module.exports = UserService;
