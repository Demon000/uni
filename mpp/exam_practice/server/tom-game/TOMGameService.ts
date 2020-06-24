import User from '../../common/domain/User';

import GameService from '../base-game/GameService';

import GameRoom from '../base-game/GameRoom';

import TOMAnswer, {ITOMAnswer} from '../../common/tom-game/TOMAnswer';
import TOMQuestion from '../../common/tom-game/TOMQuestion';
import {QuestionType} from '../../common/base-game/Question';

export default class TOMGameService extends GameService {
    protected readonly _neededNoPlayers: number;
    protected readonly _neededNoRounds: number;
    private readonly _letters: string[];

    constructor(neededNoPlayers: number, neededNoRounds: number, letters: string[]) {
        super();

        this._neededNoPlayers = neededNoPlayers;
        this._neededNoRounds = neededNoRounds;
        this._letters = letters;
    }

    createRoom(): GameRoom {
        return new GameRoom(this._neededNoPlayers, this._neededNoRounds,
            QuestionType.COMPUTER_GENERATED);
    }

    getRandomLetter() {
        const index = Math.floor(Math.random() * this._letters.length);
        return this._letters[index];
    }

    createComputerQuestion() {
        const letter = this.getRandomLetter();
        return new TOMQuestion({
            letter: letter,
        });
    }

    createPlayerQuestion(...args: any[]) {
        return undefined;
    }

    createPlayerAnswer(options: ITOMAnswer) {
        return new TOMAnswer(options);
    }

    evaluateRoomAnswers(room: GameRoom): void {
        const answers = room.getCurrentRoundAnswers();
        for (const answer of answers) {
            answer.points = Math.floor(Math.random() * 10);
        }
    }
}
