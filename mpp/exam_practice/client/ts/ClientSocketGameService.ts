import EventEmitter from 'eventemitter3';

import {GameServiceEvents, IGameService} from '../../common/service/IGameService';
import {IGameRoomState} from '../../common/domain/IGameRoomState';
import {GameSocketEvents} from '../../common/socket/GameSocket';

import {getAccessTokenPayload} from './store';
import ISafeUser from '../../common/domain/ISafeUser';
import IAnswer from '../../common/domain/IAnswer';

export default class ClientSocketGameService extends EventEmitter implements IGameService {
    private readonly _socket: SocketIOClient.Socket;

    constructor(socket: SocketIOClient.Socket) {
        super();

        this._socket = socket;

        this._socket.on('connect', () => {
            this.onConnect();
        });

        this._socket.on(GameServiceEvents.ROOM_UPDATE, (room: IGameRoomState) => {
            this.onRoomUpdate(room);
        });
    }

    private onConnect() {
        const accessTokenPayload = getAccessTokenPayload();
        this._socket.emit(GameSocketEvents.AUTHORIZE, accessTokenPayload);
    }

    private onRoomUpdate(room: IGameRoomState) {
        console.log(room);
        this.emit(GameServiceEvents.ROOM_UPDATE, room);
    }

    createAndAddPlayerAnswer(player: ISafeUser, questionId: number, answerOptions: IAnswer): void {
        this._socket.emit(GameSocketEvents.USER_ANSWER, questionId, answerOptions);
    }

    startRoom(player: ISafeUser): void {
        this._socket.emit(GameSocketEvents.ROOM_START);
    }

    joinRoom(player: ISafeUser): void {
        this._socket.emit(GameSocketEvents.JOIN_ROOM);
    }

    leaveRoom(player: ISafeUser): void {
        this._socket.emit(GameSocketEvents.LEAVE_ROOM);
    }
}
