import {Namespace, Socket} from 'socket.io';

import User from '../domain/User';

import {AccessTokenError, UserNotFoundError} from '../lib/Errors';

import AuthService from '../service/AuthService';
import UserService from '../service/UserService';
import GameService, {BaseGameEvents} from './GameService';

enum SocketGameEvents {
    CONNECTION = 'connection',
    AUTHORIZE = 'authorize',
    ROOM_START = 'room-start',
    USER_ANSWER = 'user-answer',
    USER_QUESTION = 'user-question',
    DISCONNECT = 'disconnect',
}

export default class GameSocket {
    private _userService: UserService;
    private _authService: AuthService;
    private _gameService: GameService;
    private _io: Namespace;

    private socketUserMap: {[key: string]: User} = {};

    constructor(io: Namespace, userService: UserService, authService: AuthService, gameService: GameService) {
        this._io = io;
        this._userService = userService;
        this._authService = authService;
        this._gameService = gameService;

        this._io.on(SocketGameEvents.CONNECTION, this.onConnection);
        this._gameService.on(BaseGameEvents.ROOM_UPDATE, this.onRoomUpdate);
    }

    onConnection(socket: Socket) {
        console.log(`connected: ${socket.id}`);

        socket.on(SocketGameEvents.AUTHORIZE, this.onAuthorize);
        socket.on(SocketGameEvents.ROOM_START, this.onRoomStart);
        socket.on(SocketGameEvents.USER_ANSWER, this.onUserAnswer);
        socket.on(SocketGameEvents.USER_QUESTION, this.onUserQuestion);
        socket.on(SocketGameEvents.DISCONNECT, this.onDisconnect);
    }

    getUser(socket: Socket): User {
        return this.socketUserMap[socket.id];
    }

    getSocket(user: User): Socket | undefined {
        const socketIds = Object.keys(this.socketUserMap);
        const socketId = socketIds.find(socketId => this.socketUserMap[socketId].id === user.id);
        if (!socketId) {
            return undefined;
        }

        return this._io.sockets[socketId];
    }

    addUser(socket: Socket, user: User) {
        console.log(`adding socket: ${socket.id}, user: ${user}`);
        this.socketUserMap[socket.id] = user;
        this._gameService.addPlayer(user);
    }

    removeUser(socket: Socket) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        console.log(`removing socket: ${socket.id}, user: ${user}`);
        delete this.socketUserMap[socket.id];
        this._gameService.removePlayer(user);
    }

    async onAuthorize(socket: Socket, payload: string, responseFn: Function) {
        let accessToken;
        try {
            accessToken = this._authService.getAccessTokenFromPayload(payload);
        } catch (e) {
            return responseFn(null, new AccessTokenError());
        }

        let user;
        try {
            user = await this._userService.getUserById(accessToken.user.id);
        } catch (e) {
            return responseFn(null, new UserNotFoundError());
        }

        try {
            this.addUser(socket, user);
        } catch (e) {
            return responseFn(null, e);
        }

        responseFn(user.toResponse(), null);
    }

    onRoomStart(socket: Socket, responseFn: Function) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        try {
            this._gameService.startRoom(user);
        } catch (e) {
            return responseFn(e);
        }

        responseFn(null);
    }

    onRoomUpdate(user: User, room: any) {
        const socket = this.getSocket(user);
        if (!socket) {
            return;
        }

        socket.emit(BaseGameEvents.ROOM_UPDATE, room);
    }

    onUserAnswer(socket: Socket, questionId: number, ...args: any[]) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        this._gameService.createAndAddPlayerAnswer(user, questionId, ...args);
    }

    onUserQuestion(socket: Socket, ...args: any[]) {
        const user = this.getUser(socket);
        if (!user) {
            return;
        }

        this._gameService.createAndAddPlayerQuestion(user, ...args);
    }

    onDisconnect(socket: Socket, responseFn: Function) {
        try {
            this.removeUser(socket);
        } catch (e) {
            return responseFn(e);
        }

        responseFn(null);
    }
}
