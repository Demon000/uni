const router = require('express').Router();

const UserService = require('../services/UserService');
const UserRoles = require('../models/UserRoles');

const { authUserWithRole } = require('./auth_common');

router.get('/',
        authUserWithRole(UserRoles.ADMIN),
        async (req, res) => {
    const users = await UserService.getUsers();
    res.send(users);
});

router.get('/roles',
        async (req, res) => {
    res.send(UserRoles.getValues());
});

router.post('/',
        authUserWithRole(UserRoles.ADMIN),
        async (req, res) => {
    const user = await UserService.createUser(req.body);
    res.send(user);
});

module.exports = router;
