import * as http from 'http';


import {Express, json, urlencoded} from 'express';
import CookieParser from 'cookie-parser';
import Cors from 'cors';

import Logger from 'morgan';
import SocketIO from 'socket.io';
import {createConnection} from 'typeorm';

import Config from './config';

import UserSchema from './server/schema/UserSchema';

import UserRepository from './server/repository/UserRepository';
import UserService from './server/service/UserService';

import TokenGenerator from './server/lib/TokenGenerator';
import AuthService from './server/service/AuthService';

import ApiRouter from './server/router/ApiRouter';

import TOMGameService from './server/tom-game/TOMGameService';
import GameSocket from './server/base-game/GameSocket';

export default async function(app: Express, server: http.Server) {
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

    const apiRouter = ApiRouter(userService, authService);
    app.use('/api', apiRouter);

    const io = SocketIO().listen(server);

    const tomGameService = new TOMGameService(3, 3, ['A', 'B', 'C']);
    const tomGameNamespace = io.of('tom');
    new GameSocket(tomGameNamespace, userService, authService, tomGameService);
}
