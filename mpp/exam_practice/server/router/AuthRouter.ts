import {Router} from 'express';

import UserService from '../service/UserService';
import AuthService from '../service/AuthService';
import {AuthMiddleware} from './AuthMiddleware';

export default function(userService: UserService, authService: AuthService, authMiddleware: AuthMiddleware) {
    const router = Router();

    router.post('/login', async (req, res) => {
        const user = await userService.getUserByUsername(req.body.username);
        await userService.verifyPassword(user, req.body.password);
        const accessTokenPayload = authService.createAccessTokenPayload(user);

        res.send({
            user: user.toResponse(),
            access_token: accessTokenPayload,
        });
    });

    router.get('/user', authMiddleware.checkUser, (req, res) => {
        res.send(res.locals.user.toResponse());
    });

    return router;
}
