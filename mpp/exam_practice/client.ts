import * as http from 'http';
import * as Express from 'express';

export default async function(app: Express.Express, server: http.Server) {
    app.use(Express.static('client'));
}
