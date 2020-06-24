import Config from './config';

import http from 'http';
import Express, {json, urlencoded} from 'express';
import Logger from 'morgan';
import CookieParser from 'cookie-parser';
import Cors from 'cors';

const app = Express();
const httpServer = http.createServer(app);

require('express-async-errors');

const logger = Logger(Config.Logger.format);
app.use(logger);

const jsonParser = json();
app.use(jsonParser);

const urlEncodedParser = urlencoded({
    extended: false
});
app.use(urlEncodedParser);

const cookieParser = CookieParser();
app.use(cookieParser);

const cors = Cors(Config.Cors);
app.use(cors);
app.options('*', cors);

import ClientServer from './client';
ClientServer(app, httpServer)
    .then(() => {
        console.log('Successfully added client routes');
    })
    .catch(e => {
        console.log('Failed to add client routes', e);
    });

import ApiServer from './server';
ApiServer(app, httpServer)
    .then(() => {
        console.log('Successfully added api server routes');
    })
    .catch(e => {
        console.log('Failed to add api server routes', e);
    });

httpServer.listen(Config.Server.port, Config.Server.host, () => {
    console.log('Server successfully started');
});
