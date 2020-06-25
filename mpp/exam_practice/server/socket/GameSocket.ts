import {Namespace, Socket} from 'socket.io';
import Logger from 'log4js';

import {GameServiceEvents} from '../../common/service/IGameService';
import {GameSocketEvents} from '../../common/socket/GameSocket';

import AuthService from '../service/AuthService';
import UserService from '../service/UserService';
import GameService from '../service/GameService';
import GameRoom from '../game/GameRoom';
import ISafeUser from '../../common/domain/ISafeUser';
import IQuestion from '../../common/domain/IQuestion';
import IAnswer from '../../common/domain/IAnswer';

export default class GameSocket {
    private readonly _logger: Logger.Logger;

    private readonly _userService: UserService;
    private readonly _authService: AuthService;
    private readonly _gameService: GameService;
    private readonly _io: Namespace;

    private readonly socketUserMap: {[key: string]: ISafeUser} = {};

    constructor(io: Namespace, userService: UserService, authService: AuthService, gameService: GameService) {
        this._logger = Logger.getLogger();
        this._logger.level = 'debug';

        this._io = io;
        this._userService = userService;
        this._authService = authService;
        this._gameService = gameService;

        this._io.on('connection', (socket) => {
            this.onConnection(socket);
        });

        this._gameService.on(GameServiceEvents.ROOM_UPDATE, (user: ISafeUser, room: GameRoom) => {
            this.onRoomUpdate(user, room);
        });
    }

    onConnection(socket: Socket) {
        const self = this;

        this._logger.info(`connected: ${socket.id}`);

        socket.on(GameSocketEvents.AUTHORIZE, async (payload: string) => {
            await self.onAuthorize(socket, payload);
        });

        socket.on(GameSocketEvents.ROOM_START, () => {
            self.onRoomStart(socket);
        });

        socket.on(GameSocketEvents.USER_ANSWER, (questionId: number, answerOptions: IAnswer) => {
            self.onUserAnswer(socket, questionId, answerOptions);
        });

        socket.on(GameSocketEvents.USER_QUESTION, (questionOptions: IQuestion) => {
            self.onUserQuestion(socket, questionOptions);
        });

        socket.on(GameSocketEvents.DISCONNECT, () => {
            self.onDisconnect(socket);
        });
    }

    getUser(socket: Socket): ISafeUser {
        return this.socketUserMap[socket.id];
    }

    getSocket(user: ISafeUser): Socket | undefined {
        const socketIds = Object.keys(this.socketUserMap);
        const socketId = socketIds.find(socketId => this.socketUserMap[socketId].id === user.id);
        if (!socketId) {
            return undefined;
        }

        return this._io.sockets[socketId];
    }

    addUser(socket: Socket, user: ISafeUser) {
        this._logger.info(`adding socket: ${socket.id}, user:`, user);
        this.socketUserMap[socket.id] = user;
        this._gameService.addPlayer(user);
    }

    removeUser(socket: Socket) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        this._logger.info(`removing socket: ${socket.id}, user:`, user);
        delete this.socketUserMap[socket.id];
        this._gameService.removePlayer(user);
    }

    onRoomUpdate(user: ISafeUser, room: GameRoom) {
        const socket = this.getSocket(user);
        if (!socket) {
            return;
        }

        socket.emit(GameServiceEvents.ROOM_UPDATE, room);
    }

    async onAuthorize(socket: Socket, payload: string) {
        this._logger.info(`authorizing socket: ${socket.id}`);
        let accessToken;
        try {
            accessToken = this._authService.getAccessTokenFromPayload(payload);
        } catch (e) {
            return;
        }

        let user;
        try {
            user = await this._userService.getUserById(accessToken.user.id);
        } catch (e) {
            return;
        }

        user = user.toPasswordSafe();

        try {
            this.addUser(socket, user);
        } catch (e) {
            return;
        }
    }

    onRoomStart(socket: Socket) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        try {
            this._gameService.startRoom(user);
        } catch (e) {
            console.error(e);
        }
    }

    onUserAnswer(socket: Socket, questionId: number, answerOptions: IAnswer) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        this._gameService.createAndAddPlayerAnswer(user, questionId, answerOptions);
    }

    onUserQuestion(socket: Socket, questionOptions: IQuestion) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        this._gameService.createAndAddPlayerQuestion(user, questionOptions);
    }

    onDisconnect(socket: Socket) {
        console.log(`disconnected: ${socket.id}`);

        try {
            this.removeUser(socket);
        } catch (e) {
        }
    }
}
