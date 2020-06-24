import {Router} from 'express';

import UserService from '../service/UserService';
import AuthService from '../service/AuthService';

import HelloRouter from './HelloRouter';
import AuthRouter from './AuthRouter';
import {AuthMiddleware} from './AuthMiddleware';

export default function (userService: UserService, authService: AuthService) {
    const router = Router();

    const authMiddleware = new AuthMiddleware(userService, authService);

    const helloRouter = HelloRouter();
    router.use('/hello', helloRouter);

    const authRouter = AuthRouter(userService, authService, authMiddleware);
    router.use('/auth', authRouter);

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
