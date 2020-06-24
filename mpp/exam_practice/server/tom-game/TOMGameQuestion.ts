import Question, {QuestionType} from '../base-game/Question';

export default class TOMGameQuestion extends Question {
    id: number = 0;
    letter: string;

    constructor(letter: string) {
        super();

        this.letter = letter;
    }
}
