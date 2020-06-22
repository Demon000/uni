import Config from '../config';

import {Router, json, urlencoded} from 'express';
const router = Router();

const jsonParser = json();
router.use(jsonParser);

const urlEncodedParser = urlencoded({
    extended: false
});
router.use(urlEncodedParser);

import CookieParser from 'cookie-parser';
const cookieParser = CookieParser();
router.use(cookieParser);

import Cors from 'cors';
const cors = Cors(Config.Cors);
router.use(cors);
router.options('*', cors);

import hello from './hello';
router.use('/hello', hello);

// eslint-disable-next-line no-unused-vars
// @ts-ignore
router.use((err, req, res, next) => {
    const data = {
        error: true,
        message: err.message,
    };

    // console.error(err);

    const status = err.status || 500;
    res.status(status).send(data);
});

export default router;
