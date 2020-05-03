const Config = require('config');

const User = require('../models/User');
const Errors = require('../lib/Errors');

const TokenGenerator = require('../lib/TokenGenerator');
const TokenReason = require('../lib/TokenReasons');
const TokenGeneratorConfig = Config.get('TokenGenerator');
const tokenGenerator = new TokenGenerator(TokenGeneratorConfig);

class AuthService {
    static createAccessTokenPayload(user) {
        const data = {
            reason: TokenReason.ACCESS_TOKEN,
            user,
        };

        return tokenGenerator.createAccessToken(data);
    }

    static getAccessTokenFromPayload(payload) {
        const accessToken = tokenGenerator.decodeToken(payload);
        if (accessToken.reason !== TokenReason.ACCESS_TOKEN) {
            throw new Errors.AccessTokenError();
        }

        return accessToken;
    }

    static getUserFromAccessToken(accessToken) {
        const user = accessToken.user;
        if (!user) {
            throw new Errors.AccessTokenError();
        }

        user._id = user.id;
        return User.hydrate(user);
    }
}

module.exports = AuthService;
