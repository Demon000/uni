const AuthService = require('../services/AuthService');
const Errors = require('../lib/Errors');

function authUserInner(role) {
    return (req, res, next) => {
        const header = req.headers.authorization;
        if (!header) {
            throw new Errors.AccessTokenError();
        }

        const parts = header.split(' ');
        if (parts.length !== 2) {
            throw new Errors.AccessTokenError();
        }

        const payload = parts[1];
        let accessToken;
        try {
            accessToken = AuthService.getAccessTokenFromPayload(payload);
        } catch (e) {
            throw new Errors.AccessTokenError();
        }

        res.locals.user = AuthService.getUserFromAccessToken(accessToken);

        if (role && res.locals.user.role !== role) {
            throw new Errors.UserForbiddenError();
        }

        next();
    };
}

function authUser() {
    return authUserInner();
}

function authUserWithRole(role) {
    return authUserInner(role);
}

module.exports = {
    authUser,
    authUserWithRole,
};
