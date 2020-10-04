import {Router} from 'express';

import {HelloError} from '../lib/Errors';
import GameService from '../service/GameService';

export default function(gameService: GameService) {
    const router = Router();

    router.get('/initial', (req, res) => {
        const rooms = gameService.rooms.map(room => room.toInitialGameState());
        res.send(rooms)
    });

    return router;
}
