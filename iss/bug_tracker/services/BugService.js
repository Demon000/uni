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

    static getBugsForUserQuery(userId, status=BugStatuses.ALL) {
        let query = Bug.find();

        if (userId) {
            query.forUserId(userId);
        }

        if (status === BugStatuses.SOLVED) {
            query.sort({
                solvedAt: -1,
            });
        } else if (status === BugStatuses.OPEN) {
            query.sort({
                createdAt: -1,
            });
        }

        if (status !== BugStatuses.ALL) {
            query.withStatus(status);
        }

        return query;
    }

    static countBugs(userId, status=BugStatuses.ALL) {
        const query = this.getBugsForUserQuery(userId, status);
        return query.countDocuments().exec();
    }

    static getBugs(before, entries, userId, status=BugStatuses.ALL) {
        const query = this.getBugsForUserQuery(userId, status);
        return query.skip(before).limit(entries).populateUsers().exec();
    }

    static async getBugById(userId, bugId) {
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
