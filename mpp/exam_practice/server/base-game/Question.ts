import User from '../domain/User';

export enum QuestionType {
    COMPUTER_GENERATED = 'COMPUTER_GENERATED',
    PLAYER_ADDED = 'PLAYER_ADDED',
}

export default class Question {
    round: number = 0;
    id: number = 0;
    player: User | undefined;
}
