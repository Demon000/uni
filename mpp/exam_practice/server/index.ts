import * as http from 'http';

import Express from 'express';
import Logger from 'morgan';
import SocketIO from 'socket.io';
import {createConnection} from 'typeorm';

import Config from './config';

import UserSchema from './schema/UserSchema';

import UserRepository from './repository/UserRepository';
import UserService from './service/UserService';

import TokenGenerator from './lib/TokenGenerator';
import AuthService from './service/AuthService';

import ApiRouter from './router/ApiRouter';

import TOMGameService from './tom-game/TOMGameService';
import GameSocket from './base-game/GameSocket';

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

    await userService.createTestUsers(Config.Users)
    .then(() => {
        console.log('Finished adding test users.');
    });

    require('express-async-errors');

    const app = Express();
    const server = http.createServer(app);

    const logger = Logger(Config.Logger.format);
    app.use(logger);

    const apiRouter = ApiRouter(userService, authService);
    app.use('/api', apiRouter);

    const io = SocketIO().listen(server);

    const tomGameService = new TOMGameService(3, 3, ['A', 'B', 'C']);
    const tomGameNamespace = io.of('tom');
    new GameSocket(tomGameNamespace, userService, authService, tomGameService);

    server.listen(Config.Server.port, Config.Server.host, () => {
        console.log('Server successfully started.');
    });
})();
