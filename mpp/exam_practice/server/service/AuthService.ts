import User from '../domain/User';
import {AccessTokenError} from '../lib/Errors';
import TokenGenerator from '../lib/TokenGenerator';

enum TokenReason {
    ACCESS_TOKEN = 'ACCESS_TOKEN'
}

export interface AccessToken {
    reason: TokenReason,
    user: {
        id: number,
    }
}

export default class AuthService {
    private _tokenGenerator: TokenGenerator;

    constructor(tokenGenerator: TokenGenerator) {
        this._tokenGenerator = tokenGenerator;
    }

    createAccessTokenPayload(user: User) {
        const data: AccessToken = {
            reason: TokenReason.ACCESS_TOKEN,
            user: {
                id: user.id,
            },
        };

        return this._tokenGenerator.createAccessToken(data);
    }

    getAccessTokenFromPayload(payload: string): AccessToken {
        const accessToken = this._tokenGenerator.decodeToken(payload) as AccessToken;
        if (accessToken.reason !== TokenReason.ACCESS_TOKEN) {
            throw new AccessTokenError();
        }

        return accessToken;
    }
}
