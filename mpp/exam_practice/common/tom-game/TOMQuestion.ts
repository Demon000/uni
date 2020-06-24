import Question from '../base-game/Question';

interface ITOMQuestion {
    id?: number;
    letter: string;
}

export default class TOMQuestion extends Question implements ITOMQuestion {
    id: number = 0;
    letter: string;

    constructor(options: ITOMQuestion) {
        super();

        this.letter = options.letter;
    }
}
