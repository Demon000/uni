const router = require('express').Router();

const UserService = require('../services/UserService');
const AuthService = require('../services/AuthService');

const { authUser } = require('./auth_common');

router.post('/login', async (req, res) => {
    const user = await UserService.getUserByUserName(req.body.username);
    await UserService.verifyPassword(user, req.body.password);
    const accessTokenPayload = AuthService.createAccessTokenPayload(user);

    res.send({
        user,
        'access_token': accessTokenPayload,
    });
});

router.get('/user',
        authUser(),
        (req, res) => {
    res.send(res.locals.user);
});

module.exports = router;
