const AuthService = require('../services/AuthService');
const UserRoles = require('../models/UserRoles');
const Errors = require('../lib/Errors');

function getPayloadFromHeader(req) {
    const header = req.headers.authorization;
    if (!header) {
        throw new Errors.AccessTokenError();
    }

    const parts = header.split(' ');
    if (parts.length !== 2) {
        throw new Errors.AccessTokenError();
    }

    return parts[1];
}

function getPayloadFromQuery(req) {
    return req.query.access_token;
}

function authUserInner(role, method='header') {
    return (req, res, next) => {
        let payload = null;
        if (method === 'header') {
            payload = getPayloadFromHeader(req);
        } else if (method === 'query') {
            payload = getPayloadFromQuery(req);
        }

        let accessToken;
        try {
            accessToken = AuthService.getAccessTokenFromPayload(payload);
        } catch (e) {
            throw new Errors.AccessTokenError();
        }

        res.locals.user = AuthService.getUserFromAccessToken(accessToken);

        if (UserRoles.isCompatibleRole(res.locals.user.role, role)) {
            throw new Errors.UserForbiddenError();
        }

        next();
    };
}

function authUser(method) {
    return authUserInner(null, method);
}

function authUserWithRole(role, method) {
    return authUserInner(role, method);
}

module.exports = {
    authUser,
    authUserWithRole,
};
