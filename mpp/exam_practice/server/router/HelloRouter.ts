import {Router} from 'express';

import {HelloError} from '../lib/Errors';

export default function() {
    const router = Router();

    router.get('/world', (req, res) => {
        res.send({
            message: 'Hello world.',
        });
    });

    router.get('/error', () => {
        throw new HelloError();
    });

    return router;
}
