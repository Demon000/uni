import EventEmitter from 'eventemitter3';
import ISafeUser from '../domain/ISafeUser';
import IAnswer from '../domain/IAnswer';
import IQuestion from '../domain/IQuestion';

export enum GameServiceEvents {
    ROOM_UPDATE = 'game-room-update',
}

export interface IGameService extends EventEmitter {
    startRoom(player: ISafeUser): void;
    joinRoom(player: ISafeUser): void;
    leaveRoom(player: ISafeUser): void;
    createAndAddPlayerAnswer(player: ISafeUser, questionId: number, answerOptions: IAnswer): void;
}
