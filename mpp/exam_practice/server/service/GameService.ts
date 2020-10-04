import EventEmitter from 'eventemitter3';
import Logger from 'log4js';

import {NotPlayingError, QuestionNotFoundError} from '../lib/Errors';

import GameRoom from '../game/GameRoom';
import Answer from '../../common/domain/Answer';
import {GameServiceEvents, IGameService} from '../../common/service/IGameService';
import ISafeUser from '../../common/domain/ISafeUser';
import IAnswer from '../../common/domain/IAnswer';
import {CONFIGURATION_BLOCKED, CONFIGURATION_EMPTY, CONFIGURATION_LENGTH} from '../../common/domain/IConfiguration';
import Question from '../../common/domain/Question';
import GameRoomState from '../../common/domain/IGameRoomState';
import {GameRoomStatus} from '../../common/game/GameRoomStatus';

export default class GameService extends EventEmitter implements IGameService {
    private readonly _logger: Logger.Logger;

    protected readonly _neededNoPlayers: number;
    protected readonly _neededNoRounds: number;
    private readonly _numberOfBlockages: number;

    rooms: GameRoom[] = [];

    constructor(neededNoPlayers: number, neededNoRounds: number, numberOfBlockages: number) {
        super();

        this._logger = Logger.getLogger();
        this._logger.level = 'debug';

        this._neededNoPlayers = neededNoPlayers;
        this._neededNoRounds = neededNoRounds;
        this._numberOfBlockages = numberOfBlockages;
    }

    createRoom(): GameRoom {
        return new GameRoom({
            neededNoPlayers: this._neededNoPlayers,
            neededNoRounds: this._neededNoRounds,
        });
    }

    protected addRoom(): GameRoom {
        const room = this.createRoom();
        this._logger.info('adding room:', room);
        this.rooms.push(room);
        return room;
    }

    protected findAvailableRoom(): GameRoom | undefined {
        return this.rooms.find(room => room.status === GameRoomStatus.WAITING_FOR_PLAYERS);
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
        this._logger.info('sending player:', player, 'event:', event, 'data:', ...args);
        this.emit(event, player, ...args);
    }

    protected emitRoomUpdateForRoomPlayers(room: GameRoom) {
        for (const player of room.players) {
            const playerStateRoom = room.toPlayerState(player);
            this.emitForPlayer(player, GameServiceEvents.ROOM_UPDATE, playerStateRoom);
        }
    }

    joinRoom(player: ISafeUser) {
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

    leaveRoom(player: ISafeUser) {
        let room;
        try {
            room = this.getPlayerRoom(player);
        } catch (e) {
            console.error(e);
            return;
        }

        try {
            room.removePlayer(player);
        } catch (e) {
            console.error(e);
            return;
        }

        this._logger.info('player:', player, 'left room:', room);

        this.emitRoomUpdateForRoomPlayers(room);
    }

    protected startRoomRound(room: GameRoom) {
        room.startNextRound();
        this._logger.info(`round: ${room.round} started in room:`, room);
        this.createAndAddComputerQuestion(room);
    }

    protected endRoomRound(room: GameRoom) {
        room.endRound();
        this._logger.info(`round: ${room.round} ended in room:`, room);
    }

    startRoom(player: ISafeUser) {
        let room;
        try {
            room = this.getPlayerRoom(player);
        } catch (e) {
            console.error(e);
            return;
        }

        this._logger.info('player:', player, 'is starting room:', room);

        room.originalConfiguration = this.generateRandomConfiguration();
        this.startRoomRound(room);
        this.emitRoomUpdateForRoomPlayers(room);
    }

    protected findFurthestPlayer(room: GameRoom): ISafeUser | undefined {
        const question = room.getRoundQuestion();
        if (!question) {
            return;
        }

        for (let i = CONFIGURATION_LENGTH - 1; i >= 0 ; i--) {
            if (this.isPositionPlayerOccupied(question.configuration, i)) {
                const username = question.configuration[i];
                return room.findPlayerByUsername(username);
            }
        }

        return undefined;
    }

    protected declareRoomWinner(room: GameRoom) {
        const player = this.findFurthestPlayer(room);
        if (!player) {
            return;
        }

        room.setWinner(player);
    }

    protected addPlayerAnswer(player: ISafeUser, questionId: number, answer: Answer) {
        let room;
        try {
            room = this.getPlayerRoom(player);
        } catch (e) {
            console.error(e);
            return;
        }

        const question = this.getRoomQuestionById(room, questionId);

        room.addPlayerAnswer(player, question, answer);
        this._logger.info('player:', player, 'answered question:', question, 'with answer:', answer, 'in room:', room);

        if (room.isCurrentRoundFullyAnswered()) {
            this._logger.info('round:', room.round, 'is completely answered in room:', room);
            this.endRoomRound(room);
            if (room.isFinalRound()) {
                this.declareRoomWinner(room);
            } else {
                this.startRoomRound(room);
            }
        }

        this.emitRoomUpdateForRoomPlayers(room);
    }

    createPlayerAnswer(options: IAnswer) {
        return new Answer(options);
    }

    createAndAddPlayerAnswer(player: ISafeUser, questionId: number, answerOptions: IAnswer) {
        const answer = this.createPlayerAnswer(answerOptions);
        this.addPlayerAnswer(player, questionId, answer);
    }

    createEmptyConfiguration(): string[] {
        const configuration = [];
        for (let i = 0; i < CONFIGURATION_LENGTH; i++) {
            configuration.push(CONFIGURATION_EMPTY);
        }
        return configuration;
    }

    getRandomInRange(min: number, max: number): number {
        return Math.floor(Math.random() * (max - min) + min);
    }

    generateRandomConfiguration(): string[] {
        const configuration = this.createEmptyConfiguration();

        for (let i = 0; i < this._numberOfBlockages; i++) {
            const position = this.getRandomInRange(1, CONFIGURATION_LENGTH);
            configuration[position] = CONFIGURATION_BLOCKED;
        }

        return configuration;
    }

    findPlayerPosition(player: ISafeUser, configuration: string[]) {
        for (let i = 0; i < CONFIGURATION_LENGTH; i++) {
            if (configuration[i] === player.username) {
                return i;
            }
        }

        return -1;
    }

    isPositionEmpty(configuration: string[], position: number) {
        return configuration[position] === CONFIGURATION_EMPTY;
    }

    isPositionBlocked(configuration: string[], position: number) {
        return configuration[position] === CONFIGURATION_BLOCKED;
    }

    isPositionPlayerOccupied(configuration: string[], position: number) {
        return !this.isPositionBlocked(configuration, position) && !this.isPositionEmpty(configuration, position)
    }

    findEmptyPositionBefore(configuration: string[], beforePosition: number) {
        for (let i = beforePosition; i >= 0; i--) {
            if (this.isPositionEmpty(configuration, i)) {
                return i;
            }
        }

        return 0;
    }

    claimPosition(configuration: string[], player: ISafeUser, position: number) {
        configuration[position] = player.username;
    }

    claimPlayerPositions(configuration: string[], playersConfiguration: string[]) {
        for (let i = 0; i < CONFIGURATION_LENGTH; i++) {
            if (this.isPositionPlayerOccupied(playersConfiguration, i)) {
                configuration[i] = playersConfiguration[i];
            }
        }
    }

    unClaimPosition(configuration: string[], position: number) {
        configuration[position] = CONFIGURATION_EMPTY;
    }

    createComputerQuestion(room: GameRoom): Question {
        const configuration = room.originalConfiguration.slice();
        const playersConfiguration = this.createEmptyConfiguration();

        for (const answer of room.answers) {
            if (!answer.player) {
                continue;
            }

            const currentPosition = this.findPlayerPosition(answer.player, playersConfiguration);
            let newPosition = currentPosition + answer.roll;
            if (newPosition >= CONFIGURATION_LENGTH) {
                continue;
            }

            this.unClaimPosition(playersConfiguration, currentPosition);

            while (!this.isPositionEmpty(playersConfiguration, newPosition) ||
                    !this.isPositionEmpty(configuration, newPosition)) {
                newPosition = this.findEmptyPositionBefore(playersConfiguration, newPosition);
                newPosition = this.findEmptyPositionBefore(configuration, newPosition);
            }

            this.claimPosition(playersConfiguration, answer.player, newPosition);
        }

        this.claimPlayerPositions(configuration, playersConfiguration);

        return new Question({
            configuration: configuration,
        });
    }

    protected createAndAddComputerQuestion(room: GameRoom) {
        const question = this.createComputerQuestion(room);

        try {
            room.addComputerQuestion(question);
        } catch (e) {
            console.error(e);
            return;
        }
        this._logger.info('computer asked question:', question, 'in room:', room);

        this.emitRoomUpdateForRoomPlayers(room);
    }
}
