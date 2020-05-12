const Bug = require('../models/Bug');
const BugStatuses = require('../models/BugStatuses');

const Errors = require('../lib/Errors');

class BugService {
    static async createBug(userId, data) {
        const bug = new Bug({
            title: data.title,
            description: data.description,
            createdAt: Date.now(),
            createdBy: userId,
        });
        await bug.save();
        await bug.populateUsers();
        return bug;
    }

    static async getBugsForUser(userId, status=BugStatuses.ALL) {
        let query = Bug.find();

        if (userId) {
            query = query.forUserId(userId);
        }

        if (status === BugStatuses.SOLVED) {
            query = query.sort({
                solvedAt: -1,
            });
        } else if (status === BugStatuses.OPEN) {
            query = query.sort({
                createdAt: -1,
            });
        }

        if (status !== BugStatuses.ALL) {
            query = query.withStatus(status);
        }

        return await query.populateUsers().exec();
    }

    static async getBugs(status=BugStatuses.ALL) {
        return await this.getBugsForUser(null, status);
    }

    static async getBugByIdForUser(userId, bugId) {
        let query = Bug.findById(bugId);

        if (userId) {
            query = query.forUserId(userId);
        }

        const bug = await query.exec();
        if (!bug) {
            throw new Errors.BugNotFoundError();
        }

        await bug.populateUsers();

        return bug;
    }

    static async getBugById(bugId) {
        return this.getBugByIdForUser(null, bugId);
    }

    static async updateBug(bug, data) {
        bug.title = data.title;
        bug.description = data.description;
        await bug.save();
    }

    static async solveBugForUser(userId, bug, data) {
        bug.solvedBy = userId;
        bug.solvedAt = Date.now();
        bug.solvedMessage = data.message;
        bug.status = BugStatuses.SOLVED;
        await bug.save();
    }

    static async deleteBug(bug) {
        await bug.delete();
    }
}

module.exports = BugService;
