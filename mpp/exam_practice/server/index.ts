import Config from './config';
import UserService from './service/UserService';

UserService.createTestUsers(Config.Users)
    .then(() => {
        console.log('Finished adding test users.');
    }).catch(() => {
        console.log('Failed adding test users.');
    });

require('express-async-errors');

import Express from 'express';
const app = Express();

import Logger from 'morgan';

const logger = Logger(Config.Logger.format);
app.use(logger);

import api from './api/api';
app.use('/api', api);

app.listen(Config.Server.port, Config.Server.host, () => {
    console.log('Server successfully started.');
});
