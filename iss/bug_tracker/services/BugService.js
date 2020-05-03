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
        return bug;
    }

    static async getBugsForUser(userId, status=BugStatuses.ALL) {
        let query = Bug.forUserId(userId);
        if (status !== BugStatuses.ALL) {
            query = query.withStatus(status);
        }
        return await query.exec();
    }

    static async getBugs(status=BugStatuses.ALL) {
        let query = Bug.find();
        if (status !== BugStatuses.ALL) {
            query = query.withStatus(status);
        }
        return await query.exec();
    }

    static async getBugById(bugId) {
        const bug = await Bug.findById(bugId).exec();
        if (!bug) {
            throw new Errors.BugNotFoundError();
        }

        return bug;
    }

    static async getBugByIdForUser(userId, bugId) {
        const bug = await Bug.findById(bugId).forUserId(userId).exec();
        if (!bug) {
            throw new Errors.BugNotFoundError();
        }

        return bug;
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
        await bug.save();
    }

    static async deleteBug(bug) {
        await bug.delete();
    }
}

module.exports = BugService;
