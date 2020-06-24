import * as Express from 'express';
import {Router} from 'express';
import History from 'connect-history-api-fallback';

export default async function() {
    const router = Router();

    const history = History();
    router.use(history)

    const clientStatic = Express.static('client');
    router.use(clientStatic);

    return router;
}
