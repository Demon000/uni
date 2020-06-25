import Question from './Question';
import ISafeUser from './ISafeUser';

export default interface IAnswer {
    round: number;
    id: number;
    question: Question | undefined;
    player: ISafeUser | undefined;
    points: number;

    // TODO
    country: string;
    city: string;
    mountain: string;
}
