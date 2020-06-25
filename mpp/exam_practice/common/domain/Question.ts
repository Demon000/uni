import ISafeUser from './ISafeUser';
import IQuestion from './IQuestion';

export default class Question implements IQuestion {
    round: number;
    id: number;
    player: ISafeUser | undefined;

    // TODO
    letter: string;

    constructor(options?: Partial<IQuestion>) {
        this.round = options?.round || 0;
        this.id = options?.id || 0;
        this.player = options?.player;

        // TODO
        this.letter = options?.letter || '';
    }

    toSafe(): IQuestion {
        return {
            round: this.round,
            id: this.id,
            player: this.player,
            letter: this.letter,
        };
    }
}
