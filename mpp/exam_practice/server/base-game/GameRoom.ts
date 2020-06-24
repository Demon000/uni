import User from '../domain/User';
import Answer from './Answer';
import Question, {QuestionType} from './Question';

export enum GameRoomState {
    WAITING_FOR_PLAYERS = 'WAITING_FOR_PLAYERS',
    WAITING_TO_START = 'WAITING_TO_START',
    WAITING_FOR_QUESTIONS = 'WAITING_FOR_QUESTIONS',
    WAITING_FOR_ANSWERS = 'WAITING_FOR_ANSWERS',
    ROUND_ENDED = 'ROUND_ENDED',
    ENDED = 'ENDED',
}

export default class GameRoom {
    private readonly _neededNoPlayers: number;
    private readonly _neededNoRounds: number;
    readonly questionType: QuestionType;

    state: GameRoomState = GameRoomState.WAITING_FOR_PLAYERS;
    players: User[] = [];
    questions: Question[] = [];
    answers: Answer[] = [];
    round: number = -1;

    constructor(neededNoPlayers: number, neededNoRounds: number, questionType: QuestionType) {
        this._neededNoPlayers = neededNoPlayers;
        this._neededNoRounds = neededNoRounds;
        this.questionType = questionType;

        this.reset();
    }

    setState(state: GameRoomState) {
        this.state = state;
    }

    reset() {
        this.answers = [];
        this.round = -1;
    }

    isFull() {
        return this._neededNoPlayers == this.players.length;
    }

    isEmpty() {
        return this.players.length === 0;
    }

    findPlayerIndex(player: User) {
        return this.players.findIndex(p => p.id === player.id);
    }

    isPlaying(player: User) {
        return this.findPlayerIndex(player) > -1;
    }

    addPlayer(player: User) {
        if (this.isPlaying(player)) {
            return;
        }

        this.players.push(player);

        if (this.isFull()) {
            this.setState(GameRoomState.WAITING_TO_START);
        }
    }

    removePlayer(player: User) {
        const index = this.findPlayerIndex(player);
        if (index < 0) {
            return;
        }

        this.players.splice(index, 1);

        if (!this.isFull()) {
            this.setState(GameRoomState.WAITING_FOR_PLAYERS);
            this.reset();
        }
    }

    getCurrentRoundQuestions(): Question[] {
        return this.questions.filter(question => question.round == this.round);
    }

    isCurrentRoundComputerQuestioned(): boolean {
        const questions = this.getCurrentRoundQuestions();

        if (this.questionType === QuestionType.COMPUTER_GENERATED && questions.length === 1 &&
                !questions[0].player) {
            return true;
        }

        return false;
    }

    isCurrentRoundPlayerQuestioned(player: User): boolean {
        const questions = this.getCurrentRoundQuestions();

        for (const question of questions) {
            if (question.player?.id == player.id && question.round == this.round) {
                return true;
            }
        }

        return false;
    }

    isCurrentRoundAllPlayerQuestioned(): boolean {
        for (const player of this.players) {
            if (!this.isCurrentRoundPlayerQuestioned(player)) {
                return false;
            }
        }

        return true;
    }

    isCurrentRoundFullyQuestioned(): boolean {
        return this.isCurrentRoundComputerQuestioned() || this.isCurrentRoundAllPlayerQuestioned();
    }

    addQuestion(question: Question) {
        if (this.state !== GameRoomState.WAITING_FOR_QUESTIONS) {
            return;
        }

        if (this.isCurrentRoundFullyQuestioned()) {
            return;
        }

        question.round = this.round;
        question.id = this.questions.length;
        this.questions.push(question);

        if (this.isCurrentRoundFullyQuestioned()) {
            this.setState(GameRoomState.WAITING_FOR_ANSWERS);
        }
    }

    addComputerQuestion(question: Question) {
        if (this.questionType !== QuestionType.COMPUTER_GENERATED) {
            return;
        }

        this.addQuestion(question);
    }

    addPlayerQuestion(player: User, question: Question) {
        if (this.questionType !== QuestionType.PLAYER_ADDED) {
            return;
        }

        if (this.isCurrentRoundPlayerQuestioned(player)) {
            return;
        }

        question.player = player;
        this.addQuestion(question);
    }

    isQuestionPlayerAnswered(question: Question, player: User): boolean {
        for (const answer of this.answers) {
            if (answer.player?.id == player.id && answer.question?.id === question.id && answer.round == question.round) {
                return true;
            }
        }

        return false;
    }

    isCurrentRoundFullyAnswered(): boolean {
        for (const player of this.players) {
            const questions = this.getCurrentRoundQuestions();
            for (const question of questions) {
                if (!this.isQuestionPlayerAnswered(question, player)) {
                    return false;
                }
            }
        }

        return true;
    }

    areAllRoundsAnswered(): boolean {
        return this.round == this._neededNoRounds;
    }

    startNextRound() {
        this.round++;
        this.setState(GameRoomState.WAITING_FOR_QUESTIONS);
    }

    endRound() {
        this.setState(GameRoomState.ROUND_ENDED);
        if (this.areAllRoundsAnswered()) {
            this.setState(GameRoomState.ENDED);
        }
    }

    getCurrentRoundAnswers(): Answer[] {
        return this.answers.filter(answer => answer.round == this.round);
    }

    getQuestionById(id: number): Question | undefined {
        for (const question of this.questions) {
            if (question.id === id) {
                return question;
            }
        }

        return undefined;
    }

    addPlayerAnswer(player: User, question: Question, answer: Answer) {
        if (this.state !== GameRoomState.WAITING_FOR_ANSWERS) {
            return;
        }

        if (this.isQuestionPlayerAnswered(question, player)) {
            return;
        }

        answer.round = this.round;
        answer.player = player;
        answer.question = question;

        this.answers.push(answer);
    }
}
