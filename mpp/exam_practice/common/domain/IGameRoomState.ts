import Question from './Question';
import {GameRoomStatus} from '../game/GameRoomStatus';
import Answer from './Answer';
import IAnswer from './IAnswer';
import ISafeUser from './ISafeUser';
import IQuestion from './IQuestion';

export interface IGameRoomState {
    neededNoPlayers: number;
    neededNoRounds: number;
    status: GameRoomStatus;
    players: ISafeUser[];
    originalConfiguration: string[],
    questions: IQuestion[];
    answers: IAnswer[];
    round: number;
    winner: ISafeUser | undefined;
}

export default class GameRoomState implements IGameRoomState {
    neededNoPlayers: number;
    neededNoRounds: number;
    round: number;
    status: GameRoomStatus;
    players: ISafeUser[];
    originalConfiguration: string[];
    questions: Question[];
    answers: Answer[];
    winner: ISafeUser | undefined;

    constructor(options?: Partial<IGameRoomState>) {
        this.neededNoPlayers = options?.neededNoPlayers || 0;
        this.neededNoRounds = options?.neededNoRounds || 0;
        this.round = options?.round || -1;
        this.status = options?.status || GameRoomStatus.WAITING_FOR_PLAYERS;
        this.players = options?.players || [];
        this.originalConfiguration = options?.originalConfiguration || [];
        this.questions = options?.questions as Question[] || [];
        this.answers = options?.answers as Answer[] || [];
        this.winner = options?.winner;
    }
}
