const config = require('config');

const mongoose = require('mongoose');
const MongoConfig = config.get('Mongo');
mongoose.connect(MongoConfig.url, {
    useNewUrlParser: true,
    useCreateIndex: true,
    useUnifiedTopology: true,
});

const Express = require('express');
require('express-async-errors');
const app = Express();

const api = require('./api/api');
app.use('/api', api);

const ServerConfig = config.get('Server');
app.listen(ServerConfig.port, ServerConfig.host, () => {
    console.log(`Server successfully started.`);
});
