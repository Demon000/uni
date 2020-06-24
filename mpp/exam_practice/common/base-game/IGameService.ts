import User from '../domain/User';

export interface IGameService {
    createAndAddPlayerAnswer(player: User, questionId: number, ...args: any[]): void;
    createAndAddPlayerQuestion(player: User, ...args: any[]): void;
}
