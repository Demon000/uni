import EventEmitter from 'eventemitter3';

import {GameServiceEvents, IGameService} from '../../common/service/IGameService';
import {IGameRoomState} from '../../common/domain/IGameRoomState';
import {GameSocketEvents} from '../../common/socket/GameSocket';

import {getAccessTokenPayload} from './store';
import ISafeUser from '../../common/domain/ISafeUser';
import IAnswer from '../../common/domain/IAnswer';
import IQuestion from '../../common/domain/IQuestion';

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
        this.emit(GameServiceEvents.ROOM_UPDATE, room);
    }

    createAndAddPlayerAnswer(player: ISafeUser, questionId: number, answerOptions: IAnswer): void {
        this._socket.emit(GameSocketEvents.USER_ANSWER, questionId, answerOptions);
    }

    createAndAddPlayerQuestion(player: ISafeUser, questionOptions: IQuestion): void {
        this._socket.emit(GameSocketEvents.USER_QUESTION, questionOptions);
    }

    startRoom(player: ISafeUser): void {
        this._socket.emit(GameSocketEvents.ROOM_START);
    }
}
