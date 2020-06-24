import User from '../domain/User';

import GameService from '../base-game/GameService';

import GameRoom from '../base-game/GameRoom';

import TOMGameAnswer from './TOMGameAnswer';
import TOMGameQuestion from './TOMGameQuestion';
import {QuestionType} from '../base-game/Question';

export default class TOMGameService extends GameService {
    private readonly _letters: string[];

    constructor(neededNoPlayers: number, neededNoRounds: number, letters: string[]) {
        super(neededNoPlayers, neededNoRounds);

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
        return new TOMGameQuestion(letter);
    }

    createPlayerQuestion(...args: any[]) {
        return undefined;
    }

    createPlayerAnswer(player: User, country: string, city: string, sea: string) {
        return new TOMGameAnswer(country, city, sea);
    }

    evaluateRoomAnswers(room: GameRoom): void {
        const answers = room.getCurrentRoundAnswers();
        for (const answer of answers) {
            answer.points = Math.floor(Math.random() * 10);
        }
    }
}
