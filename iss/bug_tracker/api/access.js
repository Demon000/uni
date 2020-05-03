const AuthService = require('../services/AuthService');

function getUser(req, res, next) {
    const payload = req.cookies['x-access-token'];
    const accessToken = AuthService.getAccessTokenFromPayload(payload);

    res.locals.user = AuthService.getUserFromAccessToken(accessToken);

    next();
}

module.exports = {
    getUser,
};
