const router = require('express').Router();

const UserRoles = require('../models/UserRoles');
const BugStatuses = require('../models/BugStatuses');

const BugService = require('../services/BugService');

const { authUser } = require('./auth_common');
const { authUserWithRole } = require('./auth_common');

const ServerSideEvent = require('../lib/ServerSideEvent');
const sse = new ServerSideEvent();

function isBugAccessibleTo(bug, user) {
    if (user.role === UserRoles.PROGRAMMER) {
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

router.get('/',
        authUser(),
        async (req, res) => {
    let authoredByUserOnly = false;
    if (res.locals.user.role === UserRoles.TESTER ||
            req.query.owner === 'self') {
        authoredByUserOnly = true;
    }

    const status = BugStatuses.fromString(req.query.status);
    let bugs;
    if (authoredByUserOnly) {
        bugs = await BugService.getBugsForUser(res.locals.user.id, status);
    } else {
        bugs = await BugService.getBugs(status);
    }

    res.send(bugs);
});

router.post('/',
        authUser(),
        async (req, res) => {
    const bug = await BugService.createBug(res.locals.user.id, req.body);
    sendBug('bug-add', bug);
    res.send(bug);
});

async function getBugFromParams(req, res) {
    let authoredByUserOnly = false;
    if (res.locals.user.role === UserRoles.TESTER) {
        authoredByUserOnly = true;
    }

    let bug;
    if (authoredByUserOnly) {
        bug = await BugService.getBugByIdForUser(res.locals.user.id, req.params.id);
    } else {
        bug = await BugService.getBugById(req.params.id);
    }

    return bug;
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
    await BugService.solveBugForUser(res.locals.user.id, bug, req.body);
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
