const router = require('express').Router();
const Errors = require('../lib/Errors');

router.get('/world', async (req, res) => {
    res.send({
        message: "Hello world."
    });
});

router.get('/error', async (req, res) => {
    throw new Errors.HelloError();
});

module.exports = router;
