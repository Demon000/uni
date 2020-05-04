const Mongoose = require('mongoose');
const Types = Mongoose.Schema.Types;

const BugStatuses = require('./BugStatuses');

const schema = new Mongoose.Schema({
    title: {
        type: String,
        required: true,
    },
    description: {
        type: String,
        required: true,
    },
    status: {
        type: String,
        enum: BugStatuses.getValues(),
        default: BugStatuses.OPEN,
    },
    createdAt: {
        type: Date,
    },
    createdBy: {
        type: Types.ObjectId,
        ref: 'User',
    },
    solvedAt: {
        type: Date,
    },
    solvedBy: {
        type: Types.ObjectId,
        ref: 'User',
    },
    solvedMessage: {
        type: String,
    },
});

schema.statics.forUserId = schema.query.forUserId = function (userId) {
    return this.where('createdBy').equals(userId);
};

schema.statics.withStatus = schema.query.withStatus = function (status) {
    return this.where('status').equals(status);
};

schema.methods.populateUsers = async function() {
    await this.populate('createdBy').execPopulate();
    await this.populate('solvedBy').execPopulate();
};

schema.query.populateUsers = function() {
    return this
        .populate('createdBy')
        .populate('solvedBy');
};

schema.index({ createdAt: 1 });
schema.index({ createdBy: 1 });
schema.index({ solvedAt: 1 });
schema.index({ solvedBy: 1 });

module.exports = Mongoose.model('Bug', schema);
