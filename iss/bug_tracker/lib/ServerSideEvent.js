const Errors = require("./Errors");

class ServerSideEvent {
    constructor() {
        this.connections = {};
    }

    unsubscribeHandler(req, res) {
        delete this.connections[req.session.id];
    }

    subscribeHandler(req, res) {
        if (this.connections[req.session.id]) {
            throw new Errors.AlreadySubscribedError();
        }

        req.on('close', () => {
            this.unsubscribeHandler(req, res);
        });

        this.connections[req.session.id] = res;

        res.setHeader('Content-Type', 'text/event-stream');
        res.setHeader('Cache-Control', 'no-cache');
        res.setHeader('Connection', 'keep-alive');
        res.flushHeaders();
    }

    sendEventIf(name, data, conditionFn) {
        for (const res of Object.values(this.connections)) {
            if (!conditionFn(res)) {
                continue;
            }

            res.write(`event: ${name}\ndata: ${JSON.stringify(data)}\n\n`);
        }
    }
}

module.exports = ServerSideEvent;
