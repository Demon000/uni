import Answer from '../../common/domain/Answer';
import Question from '../../common/domain/Question';
import {GameRoomStatus} from '../../common/game/GameRoomStatus';
import GameRoomState, {IGameRoomState} from '../../common/domain/IGameRoomState';
import ISafeUser from '../../common/domain/ISafeUser';
import {QuestionType} from '../../common/game/QuestionType';
import {
    AlreadyPlayingError,
    InvalidActionError,
    InvalidAnswerError,
    InvalidQuestionError,
    NotPlayingError
} from '../lib/Errors';

export default class GameRoom {
    state: GameRoomState ;

    constructor(options?: Partial<IGameRoomState>) {
        this.state = new GameRoomState(options);
    }

    get players() {
        return this.state.players;
    }

    get round() {
        return this.state.round;
    }

    get questionType() {
        return this.state.questionType;
    }

    setStatus(status: GameRoomStatus) {
        this.state.status = status;
    }

    isFull() {
        return this.state.neededNoPlayers == this.state.players.length;
    }

    isEmpty() {
        return this.state.players.length === 0;
    }

    findPlayerIndex(player: ISafeUser) {
        return this.state.players.findIndex(p => p.id === player.id);
    }

    isPlaying(player: ISafeUser) {
        return this.findPlayerIndex(player) > -1;
    }

    addPlayer(player: ISafeUser) {
        if (this.isPlaying(player)) {
            throw new AlreadyPlayingError();
        }

        this.state.players.push(player);

        if (this.isFull()) {
            this.setStatus(GameRoomStatus.WAITING_TO_START);
        }
    }

    reset() {
        this.setStatus(GameRoomStatus.WAITING_FOR_PLAYERS);
        this.state.answers = [];
        this.state.questions = [];
        this.state.round = -1;
    }

    removePlayer(player: ISafeUser) {
        const index = this.findPlayerIndex(player);
        if (index < 0) {
            throw new NotPlayingError();
        }

        this.state.players.splice(index, 1);

        if (!this.isFull()) {
            this.reset();
        }
    }

    getCurrentRoundQuestions(): Question[] {
        return this.state.questions.filter(question => question.round == this.state.round);
    }

    isCurrentRoundComputerQuestioned(): boolean {
        const questions = this.getCurrentRoundQuestions();

        return this.state.questionType === QuestionType.COMPUTER_GENERATED && questions.length === 1 &&
            !questions[0].player;
    }

    isCurrentRoundPlayerQuestioned(player: ISafeUser): boolean {
        const questions = this.getCurrentRoundQuestions();

        for (const question of questions) {
            if (question.player?.id == player.id && question.round == this.state.round) {
                return true;
            }
        }

        return false;
    }

    isCurrentRoundAllPlayerQuestioned(): boolean {
        for (const player of this.state.players) {
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
        if (this.state.status !== GameRoomStatus.WAITING_FOR_QUESTIONS) {
            throw new InvalidActionError();
        }

        question.round = this.state.round;
        question.id = this.state.questions.length;
        this.state.questions.push(question);

        if (this.isCurrentRoundFullyQuestioned()) {
            this.setStatus(GameRoomStatus.WAITING_FOR_ANSWERS);
        }
    }

    addComputerQuestion(question: Question) {
        if (this.state.questionType !== QuestionType.COMPUTER_GENERATED) {
            throw new InvalidQuestionError();
        }

        this.addQuestion(question);
    }

    addPlayerQuestion(player: ISafeUser, question: Question) {
        if (this.state.questionType !== QuestionType.PLAYER_ADDED) {
            throw new InvalidQuestionError();
        }

        if (this.isCurrentRoundPlayerQuestioned(player)) {
            throw new InvalidQuestionError();
        }

        question.player = player;
        this.addQuestion(question);
    }

    isQuestionPlayerAnswered(question: Question, player: ISafeUser): boolean {
        for (const answer of this.state.answers) {
            if (answer.player?.id == player.id && answer.question?.id === question.id && answer.round == question.round) {
                return true;
            }
        }

        return false;
    }

    areAllQuestionsPlayerAnswered(player: ISafeUser): boolean {
        const questions = this.getCurrentRoundQuestions();
        for (const question of questions) {
            if (!this.isQuestionPlayerAnswered(question, player)) {
                return false;
            }
        }

        return true;
    }

    isCurrentRoundFullyAnswered(): boolean {
        for (const player of this.state.players) {
            if (!this.areAllQuestionsPlayerAnswered(player)) {
                return false;
            }
        }

        return true;
    }

    isFinalRound(): boolean {
        return this.state.round == this.state.neededNoRounds - 1;
    }

    startNextRound() {
        if (this.isFinalRound()) {
            return;
        }

        this.state.round++;
        this.setStatus(GameRoomStatus.WAITING_FOR_QUESTIONS);
    }

    endRound() {
        this.setStatus(GameRoomStatus.ROUND_ENDED);
        if (this.isFinalRound()) {
            this.setStatus(GameRoomStatus.ENDED);
        }
    }

    getCurrentRoundAnswers(): Answer[] {
        return this.state.answers.filter(answer => answer.round == this.state.round);
    }

    getQuestionById(id: number): Question | undefined {
        for (const question of this.state.questions) {
            if (question.id === id) {
                return question;
            }
        }

        return undefined;
    }

    addPlayerAnswer(player: ISafeUser, question: Question, answer: Answer) {
        if (this.state.status !== GameRoomStatus.WAITING_FOR_ANSWERS) {
            throw new InvalidActionError();
        }

        if (this.isQuestionPlayerAnswered(question, player)) {
            throw new InvalidAnswerError();
        }

        answer.round = this.state.round;
        answer.player = player;
        answer.question = question;

        this.state.answers.push(answer);
    }

    toPlayerState(player: ISafeUser): IGameRoomState {
        let state = this.state.status;
        if (state === GameRoomStatus.WAITING_FOR_ANSWERS && this.areAllQuestionsPlayerAnswered(player)) {
            state = GameRoomStatus.WAITING_FOR_ROUND_END;
        }

        const questions = this.state.questions.map(question => question.toSafe());
        const answers = this.state.answers.map(answer => answer.toSafe())

        return {
            neededNoRounds: this.state.neededNoRounds,
            neededNoPlayers: this.state.neededNoPlayers,
            questionType: this.state.questionType,
            players: this.state.players,
            round: this.state.round,
            status: state,
            questions,
            answers,
        };
    }
}
