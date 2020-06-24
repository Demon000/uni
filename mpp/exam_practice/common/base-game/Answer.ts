import User from '../domain/User';
import Question from './Question';

export default class Answer {
    round: number = 0;
    question: Question | undefined = undefined;
    player: User | undefined = undefined;
    points: number = 0;
}
