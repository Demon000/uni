const Config = require('config');

const router = require('express').Router();

const UserService = require('../services/UserService');
const AuthService = require('../services/AuthService');

const { getUser } = require('./access');

const AccessCookieConfig = Config.get('AccessCookie');

router.post('/login', async (req, res) => {
    const user = await UserService.getUserByUserName(req.body.username);
    await UserService.verifyPassword(user, req.body.password);

    const accessPayload = AuthService.createAccessTokenPayload(user);
    res.cookie('x-access-token', accessPayload, AccessCookieConfig);
    res.send({
        success: true
    });
});

router.get('/user', getUser, (req, res) => {
    res.send(res.locals.user);
});

module.exports = router;
