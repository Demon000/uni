const router = require('express').Router();

const UserRoles = require('../models/UserRoles');
const BugStatuses = require('../models/BugStatuses');

const BugService = require('../services/BugService');

const { authUser } = require('./auth_common');
const { authUserWithRole } = require('./auth_common');

const ServerSideEvent = require('../lib/ServerSideEvent');
const sse = new ServerSideEvent();

function isBugAccessibleTo(bug, user) {
    if (UserRoles.isCompatibleRole(user.role, UserRoles.PROGRAMMER)) {
        return true;
    }

    return bug.createdBy.id === user.id;
}

function sendBug(name, bug) {
    sse.sendEventIf(name, bug, res => isBugAccessibleTo(bug, res.locals.user));
}

router.get('/sse',
        authUser('query'),
        (req, res) => {
    sse.subscribeHandler(req, res);
});

function tryParseNumberQuery(query, value, min=null, max=null) {
    if (typeof query !== 'string') {
        return value;
    }

    const parsed = Number.parseInt(query, 10);
    if (Number.isNaN(parsed)) {
        return value;
    }

    if (min !== null && parsed < min) {
        return value;
    }

    if (max !== null && parsed > max) {
        return value;
    }

    return parsed;
}

router.get('/',
        authUser(),
        async (req, res) => {
    let user = null;
    if (UserRoles.isExactRole(res.locals.user.role, UserRoles.TESTER) ||
            req.query.owner === 'self') {
        user = res.locals.user;
    }

    const page = tryParseNumberQuery(req.query.page, 0, 0);
    const entries = tryParseNumberQuery(req.query.entries, 10, 10, 10);

    const status = BugStatuses.fromString(req.query.status);
    const count = await BugService.countBugs(user, status);
    const before = Math.min(page * entries, count);
    const after = Math.max(count - (page + 1) * entries, 0);
    const bugs = await BugService.getBugs(before, entries, user, status);

    res.send({
        count,
        before,
        after,
        data: bugs,
    });
});

router.post('/',
        authUser(),
        async (req, res) => {
    const bug = await BugService.createBug(res.locals.user.id, req.body);
    sendBug('bug-add', bug);
    res.send(bug);
});

function getBugFromParams(req, res) {
    let user = null;
    if (UserRoles.isExactRole(res.locals.user.role, UserRoles.TESTER)) {
        user = res.locals.user;
    }

    return BugService.getBugById(user, req.params.id);
}

router.get('/:id',
        authUser(),
        async (req, res) => {
    const bug = await getBugFromParams(req, res);
    res.send(bug);
});

router.post('/:id',
        authUser(),
        async (req, res) => {
    const bug = await getBugFromParams(req, res);
    await BugService.updateBug(bug, req.body);
    sendBug('bug-update', bug);
    res.send(bug);
});

router.post('/:id/solve',
        authUserWithRole(UserRoles.PROGRAMMER),
        async (req, res) => {
    const bug = await getBugFromParams(req, res);
    await BugService.solveBug(res.locals.user, bug, req.body);
    sendBug('bug-update', bug);
    res.send(bug);
});

router.delete('/:id',
        authUser(),
        async (req, res) => {
    const bug = await getBugFromParams(req, res);
    await BugService.deleteBug(bug);
    sendBug('bug-delete', bug);
    res.end();
});

module.exports = router;
