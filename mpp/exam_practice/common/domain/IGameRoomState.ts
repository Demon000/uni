import Question from './Question';
import {GameRoomStatus} from '../game/GameRoomStatus';
import Answer from './Answer';
import IAnswer from './IAnswer';
import ISafeUser from './ISafeUser';
import {QuestionType} from '../game/QuestionType';
import IQuestion from './IQuestion';

export interface IGameRoomState {
    neededNoPlayers: number;
    neededNoRounds: number;
    questionType: QuestionType;
    status: GameRoomStatus;
    players: ISafeUser[];
    questions: IQuestion[];
    answers: IAnswer[];
    round: number;
}

export default class GameRoomState implements IGameRoomState {
    neededNoPlayers: number;
    neededNoRounds: number;
    round: number;
    questionType: QuestionType;
    status: GameRoomStatus;
    players: ISafeUser[];
    questions: Question[];
    answers: Answer[];

    constructor(options?: Partial<IGameRoomState>) {
        this.neededNoPlayers = options?.neededNoPlayers || 0;
        this.neededNoRounds = options?.neededNoRounds || 0;
        this.round = options?.round || -1;
        this.questionType = options?.questionType || QuestionType.COMPUTER_GENERATED;
        this.status = options?.status || GameRoomStatus.WAITING_FOR_PLAYERS;
        this.players = options?.players || [];
        this.questions = options?.questions as Question[] || [];
        this.answers = options?.answers as Answer[] || [];
    }
}
