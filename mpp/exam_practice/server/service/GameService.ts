import EventEmitter from 'eventemitter3';
import Logger from 'log4js';

import {AlreadyPlayingError, NotPlayingError, QuestionNotFoundError} from '../lib/Errors';

import GameRoom from '../game/GameRoom';
import Answer from '../../common/domain/Answer';
import Question from '../../common/domain/Question';
import {GameServiceEvents, IGameService} from '../../common/service/IGameService';
import ISafeUser from '../../common/domain/ISafeUser';
import {QuestionType} from '../../common/game/QuestionType';
import IAnswer from '../../common/domain/IAnswer';
import IQuestion from '../../common/domain/IQuestion';

export default class GameService extends EventEmitter implements IGameService {
    private readonly _logger: Logger.Logger;

    protected readonly _neededNoPlayers: number;
    protected readonly _neededNoRounds: number;
    private readonly _letters: string[];

    private rooms: GameRoom[] = [];

    // TODO
    constructor(neededNoPlayers: number, neededNoRounds: number, letters: string[]) {
        super();

        this._logger = Logger.getLogger();
        this._logger.level = 'debug';

        this._neededNoPlayers = neededNoPlayers;
        this._neededNoRounds = neededNoRounds;
        this._letters = letters;
    }

    createRoom(): GameRoom {
        return new GameRoom({
            neededNoPlayers: this._neededNoPlayers,
            neededNoRounds: this._neededNoRounds,
            questionType: QuestionType.COMPUTER_GENERATED,
        });
    }

    protected addRoom(): GameRoom {
        const room = this.createRoom();
        this._logger.info('adding room:', room);
        this.rooms.push(room);
        return room;
    }

    protected destroyEmptyRooms() {
        this.rooms = this.rooms.filter(room => {
            if (room.isEmpty()) {
                console.log('destroying empty room:', room);
            }

            return !room.isEmpty()
        });
    }

    protected findAvailableRoom(): GameRoom | undefined {
        return this.rooms.find(room => !room.isFull());
    }

    protected findPlayerRoom(player: ISafeUser): GameRoom | undefined {
        return this.rooms.find(room => room.isPlaying(player));
    }

    protected getPlayerRoom(player: ISafeUser): GameRoom {
        const room = this.findPlayerRoom(player);
        if (!room) {
            throw new NotPlayingError();
        }

        return room;
    }

    protected getRoomQuestionById(room: GameRoom, id: number) {
        const question = room.getQuestionById(id);
        if (!question) {
            throw new QuestionNotFoundError();
        }

        return question;
    }

    protected emitForPlayer(player: ISafeUser, event: string, ...args: any[]) {
        this.emit(event, player, ...args);
    }

    protected emitRoomUpdateForRoomPlayers(room: GameRoom) {
        for (const player of room.players) {
            const playerStateRoom = room.toPlayerState(player);
            this.emitForPlayer(player, GameServiceEvents.ROOM_UPDATE, playerStateRoom);
        }
    }

    addPlayer(player: ISafeUser) {
        let room = this.findPlayerRoom(player);
        if (room) {
            return;
        }

        room = this.findAvailableRoom();
        if (!room) {
            room = this.addRoom();
        }

        try {
            room.addPlayer(player);
        } catch (e) {
            console.error(e);
            return;
        }

        this._logger.info('player:', player, 'joined room:', room);

        this.emitRoomUpdateForRoomPlayers(room);
    }

    removePlayer(player: ISafeUser) {
        const room = this.getPlayerRoom(player);

        try {
            room.removePlayer(player);
        } catch (e) {
            console.error(e);
            return;
        }

        this._logger.info('player:', player, 'left room:', room);

        this.emitRoomUpdateForRoomPlayers(room);

        this.destroyEmptyRooms();
    }

    protected startRoomRound(room: GameRoom) {
        room.startNextRound();
        this._logger.info(`round: ${room.round} started in room:`, room);

        if (room.questionType === QuestionType.COMPUTER_GENERATED) {
            this.createAndAddComputerQuestion(room);
        }
    }

    protected endRoomRound(room: GameRoom) {
        room.endRound();
        this._logger.info(`round: ${room.round} ended in room:`, room);
    }

    startRoom(player: ISafeUser) {
        const room = this.getPlayerRoom(player);

        this._logger.info('player:', player, 'is starting room:', room);

        this.startRoomRound(room);
        this.emitRoomUpdateForRoomPlayers(room);
    }

    // TODO
    evaluateRoomAnswers(room: GameRoom): void {
        const answers = room.getCurrentRoundAnswers();
        for (const answer of answers) {
            answer.points = Math.floor(Math.random() * 10);
        }
    }

    protected addPlayerAnswer(player: ISafeUser, questionId: number, answer: Answer) {
        const room = this.getPlayerRoom(player);
        const question = this.getRoomQuestionById(room, questionId);

        room.addPlayerAnswer(player, question, answer);
        this._logger.info('player:', player, 'answered question:', question, 'with answer:', answer, 'in room:', room);

        if (room.isCurrentRoundFullyAnswered()) {
            this._logger.info('round:', room.round, 'is completely answered in room:', room);
            this.evaluateRoomAnswers(room);
            this.endRoomRound(room);
            this.startRoomRound(room);
        }

        this.emitRoomUpdateForRoomPlayers(room);
    }

    // TODO
    createPlayerAnswer(options: IAnswer) {
        return new Answer(options);
    }

    createAndAddPlayerAnswer(player: ISafeUser, questionId: number, answerOptions: IAnswer) {
        const answer = this.createPlayerAnswer(answerOptions);
        this.addPlayerAnswer(player, questionId, answer);
    }

    protected addQuestion(room: GameRoom, question: Question | undefined, player: ISafeUser | undefined) {
        if (!question) {
            return;
        }

        if (player) {
            try {
                room.addPlayerQuestion(player, question);
            } catch (e) {
                console.error(e);
                return;
            }
            this._logger.info('player:', player, 'asked question:', question, 'in room:', room);
        } else {
            try {
                room.addComputerQuestion(question);
            } catch (e) {
                console.error(e);
                return;
            }
            this._logger.info('computer asked question:', question, 'in room:', room);
        }

        this.emitRoomUpdateForRoomPlayers(room);
    }

    getRandomLetter() {
        const index = Math.floor(Math.random() * this._letters.length);
        return this._letters[index];
    }

    // TODO
    createComputerQuestion() {
        const letter = this.getRandomLetter();
        return new Question({
            letter: letter,
        });
    }

    protected createAndAddComputerQuestion(room: GameRoom) {
        const question = this.createComputerQuestion();
        this.addQuestion(room, question, undefined);
    }

    // TODO
    createPlayerQuestion(questionOptions: IQuestion) {
        return undefined;
    }

    createAndAddPlayerQuestion(player: ISafeUser, questionOptions: IQuestion) {
        const room = this.getPlayerRoom(player);
        const question = this.createPlayerQuestion(questionOptions);
        this.addQuestion(room, question, player);
    }
}
