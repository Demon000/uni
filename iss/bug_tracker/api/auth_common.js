const AuthService = require('../services/AuthService');
const Errors = require('../lib/Errors');

function authUserInner(role) {
    return (req, res, next) => {
        const payload = req.cookies['x-access-token'];
        const accessToken = AuthService.getAccessTokenFromPayload(payload);

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
