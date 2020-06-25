import 'source-map-support/register'

import http from 'http';

import Express, {json, urlencoded} from 'express';
import Logger from 'morgan';
import CookieParser from 'cookie-parser';
import Cors from 'cors';

import Config from './config';

const app = Express();
const httpServer = http.createServer(app);

require('express-async-errors');

const logger = Logger(Config.Logger.format);
app.use(logger);

const jsonParser = json();
app.use(jsonParser);

const urlEncodedParser = urlencoded({
    extended: false
});
app.use(urlEncodedParser);

const cookieParser = CookieParser();
app.use(cookieParser);

const cors = Cors(Config.Cors);
app.use(cors);
app.options('*', cors);

import SocketIO from 'socket.io';
import {createConnection} from 'typeorm';

import ClientServer from './client';

import UserSchema from './server/schema/UserSchema';

import UserRepository from './server/repository/UserRepository';

import TokenGenerator from './server/lib/TokenGenerator';

import UserService from './server/service/UserService';
import AuthService from './server/service/AuthService';

import ApiRouter from './server/router/ApiRouter';

import GameSocket from './server/socket/GameSocket';
import GameService from './server/service/GameService';

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

    await userService.createTestUsers(Config.Users);

    const clientServerRouter = await ClientServer();
    app.use('/', clientServerRouter);

    const apiRouter = ApiRouter(userService, authService);
    app.use('/api', apiRouter);

    const io = SocketIO().listen(httpServer);
    const tomGameService = new GameService(2, 3, ['A', 'B', 'C']);
    const tomGameNamespace = io.of('/tom');
    new GameSocket(tomGameNamespace, userService, authService, tomGameService);

    httpServer.listen(Config.Server.port, Config.Server.host, () => {
        console.log('Server successfully started');
    });
})();
