import {Router} from 'express';

import UserService from '../service/UserService';
import AuthService from '../service/AuthService';

import HelloRouter from './HelloRouter';
import AuthRouter from './AuthRouter';
import {AuthMiddleware} from './AuthMiddleware';
import GameService from '../service/GameService';
import GameRouter from './GameRouter';

export default function (userService: UserService, authService: AuthService, gameService: GameService) {
    const router = Router();

    const authMiddleware = new AuthMiddleware(userService, authService);

    const helloRouter = HelloRouter();
    router.use('/hello', helloRouter);

    const authRouter = AuthRouter(userService, authService, authMiddleware);
    router.use('/auth', authRouter);

    const gameRouter = GameRouter(gameService);
    router.use('/games', gameRouter);

    // @ts-ignore
    router.use((err, req, res, next) => {
        const data = {
            error: true,
            message: err.message,
        };

        console.error(err);

        const status = err.status || 500;
        res.status(status).send(data);
    });

    return router;
}
