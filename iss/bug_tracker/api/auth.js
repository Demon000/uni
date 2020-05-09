const Config = require('config');

const router = require('express').Router();

const UserService = require('../services/UserService');
const AuthService = require('../services/AuthService');

const { authUser } = require('./auth_common');

const AccessCookieConfig = Config.get('AccessCookie');

router.post('/login', async (req, res) => {
    const user = await UserService.getUserByUserName(req.body.username);
    await UserService.verifyPassword(user, req.body.password);
    const payload = AuthService.createAccessTokenPayload(user);

    res.cookie('x-access-token', payload, AccessCookieConfig);
    res.send({
        user,
    });
});

router.get('/user',
        authUser(),
        (req, res) => {
    res.send(res.locals.user);
});

module.exports = router;
