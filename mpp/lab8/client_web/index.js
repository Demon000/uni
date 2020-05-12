const Config = require('config');

const Express = require('express');
const app = Express();

const web = Express.static('web');
app.use('/', web);

const ServerConfig = Config.get('Server');
app.listen(ServerConfig.port, ServerConfig.host, () => {
    console.log('Server successfully started.');
});
