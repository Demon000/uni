const Config = require('config');

const mongoose = require('mongoose');
const MongoConfig = Config.get('Mongo');
mongoose.connect(MongoConfig.url, {
    useNewUrlParser: true,
    useCreateIndex: true,
    useUnifiedTopology: true,
}).then(() => {
    console.log('Mongoose successfully connected.');
}).catch(() => {
    console.log('Mongoose failed to connect.');
});

const Express = require('express');
require('express-async-errors');
const app = Express();

const api = require('./api/api');
app.use('/api', api);

const ServerConfig = Config.get('Server');
app.listen(ServerConfig.port, ServerConfig.host, () => {
    console.log('Server successfully started.');
});
