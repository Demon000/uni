import IAnswer from './IAnswer';
import Question from './Question';
import ISafeUser from './ISafeUser';

export default class Answer implements IAnswer {
    round: number;
    id: number;
    question: Question | undefined;
    player: ISafeUser | undefined ;
    points: number;

    // TODO
    country: string;
    city: string;
    mountain: string;

    constructor(options?: Partial<IAnswer>) {
        this.round = options?.round || 0;
        this.id = options?.id || 0;
        this.question = options?.question;
        this.player = options?.player;
        this.points = options?.points || 0;

        // TODO
        this.country = options?.country || '';
        this.city = options?.city || '';
        this.mountain = options?.mountain || '';
    }

    toSafe(): IAnswer {
        return {
            id: this.id,
            round: this.round,
            question: this.question,
            player: this.player,
            points: this.points,
            country: '',
            city: '',
            mountain: '',
        };
    }
}
