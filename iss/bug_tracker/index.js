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

const PrettyPrintDocuments = require('./lib/PrettyPrintDocuments');
mongoose.plugin(PrettyPrintDocuments, {
    hidden: {
        password: true,
    },
});

const UserService = require('./services/UserService');
UserService.createTestUsers().then(() => {
    console.log('Finished adding test users.');
}).catch(() => {
    console.log('Failed adding test users.');
});

const Express = require('express');
require('express-async-errors');
const app = Express();

const Session = require('express-session');
const SessionConfig = Config.get('Session');
const session = Session(SessionConfig);
app.use(session);

const LoggerConfig = Config.get('Logger');
const Logger = require('morgan');
const logger = Logger(LoggerConfig.format);
app.use(logger);

const History = require('connect-history-api-fallback');
const history = History();
app.use(history);

const web = Express.static('web');
app.use('/', web);

const api = require('./api/api');
app.use('/api', api);

const ServerConfig = Config.get('Server');
app.listen(ServerConfig.port, ServerConfig.host, () => {
    console.log('Server successfully started.');
});
