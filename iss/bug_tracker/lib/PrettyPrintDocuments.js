const MongooseHidden = require('mongoose-hidden');
const mongooseHidden = MongooseHidden();

module.exports = function(Schema, options) {
    Schema.set('toJSON', {
        virtuals: true,
    });

    Schema.set('toObject', {
        virtuals: true,
    });

    Schema.plugin(mongooseHidden, options);
};
