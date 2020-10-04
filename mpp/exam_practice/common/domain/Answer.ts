import IAnswer from './IAnswer';
import Question from './Question';
import ISafeUser from './ISafeUser';

export default class Answer implements IAnswer {
    round: number;
    id: number;
    question: Question | undefined;
    player: ISafeUser | undefined ;

    roll: number;

    constructor(options?: Partial<IAnswer>) {
        this.round = options?.round || 0;
        this.id = options?.id || 0;
        this.question = options?.question;
        this.player = options?.player;
        this.roll = options?.roll || 0;
    }

    toSafe(): IAnswer {
        return {
            id: this.id,
            round: this.round,
            question: this.question,
            player: this.player,
            roll: this.roll,
        };
    }
}
