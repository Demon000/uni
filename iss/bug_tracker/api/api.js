const Express = require('express');
const router = Express.Router();

const jsonParser = Express.json();
router.use(jsonParser);

const urlEncodedParser = Express.urlencoded({
    extended: false
});
router.use(urlEncodedParser);

const CookieParser = require('cookie-parser');
const cookieParser = CookieParser();
router.use(cookieParser);

const hello = require('./hello');
router.use('/hello', hello);

const auth = require('./auth');
router.use('/auth', auth);

// eslint-disable-next-line no-unused-vars
router.use((err, req, res, next) => {
    const data = {
        error: true,
        message: err.message,
        reason: err.name,
    };

    const status = err.status || 500;
    res.status(status).send(data);
});

module.exports = router;
