import {Request, Response, NextFunction} from 'express';

import UserService from '../service/UserService';
import AuthService from '../service/AuthService';
import {AccessTokenError} from '../lib/Errors';

export class AuthMiddleware {
    private _userService: UserService;
    private _authService: AuthService;
    checkUser: OmitThisParameter<(req: Request, res: Response, next: NextFunction) => Promise<void>>;

    constructor(userService: UserService, authService: AuthService) {
        this._userService = userService;
        this._authService = authService;
        this.checkUser = this.innerCheckUser.bind(this);
    }

    getPayloadFromHeader(req: Request) {
        const header = req.headers.authorization;
        if (!header) {
            throw new AccessTokenError();
        }

        const parts = header.split(' ');
        if (parts.length !== 2) {
            throw new AccessTokenError();
        }

        return parts[1];
    }

    async innerCheckUser(req: Request, res: Response, next: NextFunction) {
        const payload = this.getPayloadFromHeader(req);

        let accessToken;
        try {
            accessToken = this._authService.getAccessTokenFromPayload(payload);
        } catch (e) {
            throw new AccessTokenError();
        }

        res.locals.user = await this._userService.getUserById(accessToken.user.id);

        next();
    }
}
