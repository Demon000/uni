const Mongoose = require('mongoose');
const Types = Mongoose.Schema.Types;

const schema = new Mongoose.Schema({
    title: {
        type: String,
        required: true,
    },
    description: {
        type: String,
        required: true,
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
});

schema.index({ createdAt: 1 });
schema.index({ createdBy: 1 });
schema.index({ solvedAt: 1 });
schema.index({ solvedBy: 1 });

module.exports = Mongoose.model('Bug', schema);
