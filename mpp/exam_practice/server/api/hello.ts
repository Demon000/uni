import {Router} from 'express';

import {HelloError} from '../lib/Errors';

const router = Router();
router.get('/world', (req, res) => {
    res.send({
        message: 'Hello world.',
    });
});

router.get('/error', () => {
    throw new HelloError();
});

export default router;
