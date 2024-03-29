import Answer from '../../common/domain/Answer';
import Question from '../../common/domain/Question';
import {GameRoomStatus} from '../../common/game/GameRoomStatus';
import GameRoomState, {IGameRoomState} from '../../common/domain/IGameRoomState';
import ISafeUser from '../../common/domain/ISafeUser';
import {AlreadyPlayingError, InvalidActionError, InvalidAnswerError, NotPlayingError} from '../lib/Errors';

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

    get status() {
        return this.state.status;
    }

    get originalConfiguration() {
        return this.state.originalConfiguration;
    }

    get answers() {
        return this.state.answers;
    }

    set originalConfiguration(configuration: string[]) {
        this.state.originalConfiguration = configuration;
    }

    setWinner(player: ISafeUser) {
        this.state.winner = player;
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

    findPlayerByUsername(username: string) {
        return this.state.players.find(player => player.username === username);
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
        if (this.status === GameRoomStatus.ENDED) {
            return;
        }

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

        if (this.status !== GameRoomStatus.WAITING_FOR_PLAYERS) {
            this.setStatus(GameRoomStatus.ENDED);
        }
    }

    getRoundQuestion(round: number=this.round): Question | undefined {
        return this.state.questions.find(question => question.round == round);
    }

    isCurrentRoundFullyQuestioned(): boolean {
        const question = this.getRoundQuestion();
        return !!question;
    }

    addComputerQuestion(question: Question) {
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

    isQuestionPlayerAnswered(question: Question, player: ISafeUser): boolean {
        for (const answer of this.state.answers) {
            if (answer.player?.id == player.id && answer.question?.id === question.id && answer.round == question.round) {
                return true;
            }
        }

        return false;
    }

    isCurrentRoundPlayerAnswered(player: ISafeUser): boolean {
        const question = this.getRoundQuestion();
        if (!question) {
            return false;
        }

        if (!this.isQuestionPlayerAnswered(question, player)) {
            return false;
        }

        return true;
    }

    isCurrentRoundFullyAnswered(): boolean {
        for (const player of this.state.players) {
            if (!this.isCurrentRoundPlayerAnswered(player)) {
                return false;
            }
        }

        return true;
    }

    isFinalRound(): boolean {
        return this.state.round == this.state.neededNoRounds - 1;
    }

    startNextRound() {
        this.state.round++;
        this.setStatus(GameRoomStatus.WAITING_FOR_QUESTIONS);
    }

    endRound() {
        this.setStatus(GameRoomStatus.ROUND_ENDED);
        if (this.isFinalRound()) {
            this.setStatus(GameRoomStatus.ENDED);
        }
    }

    getRoundAnswers(round: number=this.round): Answer[] {
        return this.state.answers.filter(answer => answer.round == round);
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
        let status = this.state.status;
        if (status === GameRoomStatus.WAITING_FOR_ANSWERS && this.isCurrentRoundPlayerAnswered(player)) {
            status = GameRoomStatus.WAITING_FOR_EVERYONE_TO_ANSWER;
        }

        const questions = this.state.questions.map(question => question.toSafe());
        const answers = this.state.answers.map(answer => answer.toSafe())

        return {
            neededNoRounds: this.state.neededNoRounds,
            neededNoPlayers: this.state.neededNoPlayers,
            players: this.state.players,
            round: this.state.round,
            winner: this.state.winner,
            originalConfiguration: this.originalConfiguration,
            status,
            questions,
            answers,
        };
    }

    toInitialGameState(): Partial<IGameRoomState> {
        return {
            players: this.state.players,
            originalConfiguration: this.originalConfiguration,
        };
    }
}
