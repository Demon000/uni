var koa = require('koa');
var app = module.exports = new koa();
const server = require('http').createServer(app.callback());
const WebSocket = require('ws');
const wss = new WebSocket.Server({server});
const Router = require('koa-router');
const cors = require('@koa/cors');
const bodyParser = require('koa-bodyparser');

app.use(bodyParser());

app.use(cors());

app.use(middleware);

function middleware(ctx, next) {
  const start = new Date();
  return next().then(() => {
    const ms = new Date() - start;
    console.log(`${start.toLocaleTimeString()} ${ctx.request.method} ${ctx.request.url} ${ctx.response.status} - ${ms}ms`);
  });
}

const getRandomInt = (min, max) => {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min)) + min;
};

const spaces = [];
const names = ['A', 'B', 'C'];
const statuses = ['free', 'taken'];

for (let i = 0; i < 50; i++) {
  spaces.push({
    id: i + 1,
    number: names[getRandomInt(0, names.length)] + i,
    address: "location " + getRandomInt(1, 10),
    status: statuses[getRandomInt(0, statuses.length)],
  });
}

const router = new Router();

router.get('/space', ctx => {
  const status = ctx.query.status
  ctx.response.body = status ? spaces.filter(obj => obj.status === status) : spaces;
  ctx.response.status = 200;
});

const broadcast = data => {
  const stringifiedData = JSON.stringify(data);
  console.log(`boadcast ${stringifiedData}`);
  wss.clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(stringifiedData);
    }
  });
};

router.post('/space', ctx => {
  const headers = ctx.request.body;
  const number = headers.number;
  const address = headers.address;
  if (typeof number !== 'undefined'
    && typeof address !== 'undefined') {
    const index = spaces.findIndex(obj => obj.number == number);
    if (index !== -1) {
      ctx.response.body = {text: 'Space already exists!'};
      ctx.response.status = 404;
    } else {
      const maxId = Math.max.apply(Math, spaces.map(function (obj) {
        return obj.id;
      })) + 1;
      let obj = {
        id: maxId,
        number,
        address,
        status: statuses[0],
      };
      spaces.push(obj);
      broadcast(obj);
      ctx.response.body = obj;
      ctx.response.status = 200;
    }
  } else {
    ctx.response.body = {text: 'Missing or invalid fields!'};
    ctx.response.status = 404;
  }
});

router.patch('/space/:id', ctx => {
  const id = ctx.params.id;
  if (typeof id !== 'undefined') {
    const index = spaces.findIndex(obj => obj.id == id);
    if (index === -1) {
      ctx.response.body = {text: 'Invalid space id'};
      ctx.response.status = 404;
    } else {
      Object.assign(spaces[index], ctx.request.body);
      ctx.response.body = spaces[index];
      ctx.response.status = 200;
      broadcast(spaces[index]);
    }
  } else {
    ctx.response.body = {text: 'Id missing or invalid'};
    ctx.response.status = 404;
  }
});

app.use(router.routes());
app.use(router.allowedMethods());

server.listen(3000);
