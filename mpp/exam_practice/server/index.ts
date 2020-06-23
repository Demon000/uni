import Config from './config';
import Express from 'express';
import Logger from 'morgan';
import {createConnection} from 'typeorm';

import UserSchema from './schema/UserSchema';

import UserRepository from './repository/UserRepository';
import UserService from './service/UserService';

import TokenGenerator from './lib/TokenGenerator';
import AuthService from './service/AuthService';

import ApiRouter from './routers/ApiRouter';

(async function() {
    const connection = await createConnection({
        ...Config.Database,
        synchronize: true,
        entities: [
            UserSchema,
        ],
    });

    const userRepository = connection.getCustomRepository(UserRepository);
    const userService = new UserService(userRepository);

    const tokenGenerator = new TokenGenerator(Config.TokenGenerator);
    const authService = new AuthService(tokenGenerator);

    userService.createTestUsers(Config.Users)
        .then(() => {
            console.log('Finished adding test users.');
        }).catch(() => {
        console.log('Failed adding test users.');
    });

    require('express-async-errors');

    const app = Express();

    const logger = Logger(Config.Logger.format);
    app.use(logger);

    const apiRouter = ApiRouter(userService, authService);
    app.use('/api', apiRouter);

    app.listen(Config.Server.port, Config.Server.host, () => {
        console.log('Server successfully started.');
    });
})();
