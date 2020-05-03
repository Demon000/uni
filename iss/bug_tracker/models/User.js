const Mongoose = require('mongoose');
const PasswordEncrypt = require('mongoose-bcrypt');

const UserRoles = require('./UserRoles');

const schema = new Mongoose.Schema({
    username: {
        type: String,
        required: true,
        minlength: 4,
    },
    password: {
        type: String,
        required: true,
        bcrypt: true,
        minlength: 8,
    },
    role: {
        type: String,
        required: true,
        enum: UserRoles.getValues(),
    },
});

schema.index({
    username: 1,
}, {
    unique: true,
});

schema.statics.findByUsername = function(username) {
    return this.findOne({
        username,
    });
};

schema.plugin(PasswordEncrypt);

module.exports = Mongoose.model('User', schema);
