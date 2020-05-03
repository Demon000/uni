const router = require('express').Router();

const Errors = require('../lib/Errors');

router.get('/world', (req, res) => {
    res.send({
        message: 'Hello world.',
    });
});

router.get('/error', () => {
    throw new Errors.HelloError();
});

module.exports = router;
