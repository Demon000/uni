import Question, {QuestionType} from './Question';
import {GameRoomState} from './GameRoomState';
import User from '../domain/User';
import Answer from './Answer';

export interface IGameRoom {
    neededNoPlayers: number;
    neededNoRounds: number;
    questionType: QuestionType;
    state: GameRoomState;
    players: User[];
    questions: Question[];
    answers: Answer[];
    round: number;
}
