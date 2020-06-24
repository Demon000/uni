import {EventEmitter} from 'events';

import User from '../domain/User';

import {AlreadyPlayingError, NotPlayingError, QuestionNotFoundError} from '../lib/Errors';

import GameRoom from './GameRoom';
import Answer from './Answer';
import Question, {QuestionType} from './Question';

export enum BaseGameEvents {
    ROOM_UPDATE = 'game-room-update',
}

export default abstract class GameService extends EventEmitter {
    protected readonly _neededNoPlayers: number;
    protected readonly _neededNoRounds: number;

    private rooms: GameRoom[] = [];

    protected constructor(neededNoPlayers: number, neededNoRounds: number) {
        super();

        this._neededNoPlayers = neededNoPlayers;
        this._neededNoRounds = neededNoRounds;
    }

    abstract createRoom(): GameRoom;

    protected addRoom(): GameRoom {
        const room = this.createRoom();
        console.log(`adding room: ${room}`);
        this.rooms.push(room);
        return room;
    }

    protected destroyEmptyRooms() {
        this.rooms = this.rooms.filter(room => !room.isEmpty());
    }

    protected findAvailableRoom(): GameRoom | undefined {
        return this.rooms.find(room => !room.isFull());
    }

    protected findPlayerRoom(player: User): GameRoom | undefined {
        return this.rooms.find(room => room.isPlaying(player));
    }

    protected getPlayerRoom(player: User): GameRoom {
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

    protected emitForRoomPlayers(room: GameRoom, event: string, ...args: any[]) {
        for (const player of room.players) {
            this.emit(event, player, ...args);
        }
    }

    addPlayer(player: User) {
        let room = this.findPlayerRoom(player);
        if (room) {
            throw new AlreadyPlayingError();
        }

        room = this.findAvailableRoom();
        if (!room) {
            room = this.addRoom();
        }

        console.log(`player: ${player} is joining room: ${room}`);
        room.addPlayer(player);

        this.emitForRoomPlayers(room, BaseGameEvents.ROOM_UPDATE, room);
    }

    removePlayer(player: User) {
        const room = this.getPlayerRoom(player);

        console.log(`player: ${player} is leaving room: ${room}`);
        room.removePlayer(player);

        this.emitForRoomPlayers(room, BaseGameEvents.ROOM_UPDATE, room);

        this.destroyEmptyRooms();
    }

    protected startRoomRound(room: GameRoom) {
        room.startNextRound();
        console.log(`round: ${room.round} started in ${room}`);

        if (!room.areAllRoundsAnswered() && room.questionType === QuestionType.COMPUTER_GENERATED) {
            this.createAndAddComputerQuestion(room);
        }
    }

    protected endRoomRound(room: GameRoom) {
        room.endRound();
        console.log(`round: ${room.round} ended in ${room}`);
    }

    startRoom(player: User) {
        const room = this.getPlayerRoom(player);

        console.log(`player: ${player} is starting room: ${room}`);

        this.startRoomRound(room);
        this.emitForRoomPlayers(room, BaseGameEvents.ROOM_UPDATE, room);
    }

    abstract evaluateRoomAnswers(answers: GameRoom): void;

    protected addPlayerAnswer(player: User, questionId: number, answer: Answer) {
        const room = this.getPlayerRoom(player);
        const question = this.getRoomQuestionById(room, questionId);

        console.log(`player: ${player} is answering question: ${question} with answer: ${answer} in room: ${room}`);
        room.addPlayerAnswer(player, question, answer);
        if (room.isCurrentRoundFullyAnswered()) {
            console.log(`round: ${room.round} is completely answered in room: ${room}`);
            this.evaluateRoomAnswers(room);
            this.endRoomRound(room);
            this.startRoomRound(room);

            this.emitForRoomPlayers(room, BaseGameEvents.ROOM_UPDATE, room);
        }
    }

    abstract createPlayerAnswer(player: User, ...args: any[]): Answer;

    createAndAddPlayerAnswer(player: User, questionId: number, ...args: any[]) {
        const answer = this.createPlayerAnswer(player, ...args);
        this.addPlayerAnswer(player, questionId, answer);
    }

    protected addQuestion(room: GameRoom, question: Question | undefined, player: User | undefined) {
        if (!question) {
            return;
        }

        if (player) {
            console.log(`asking question: ${question} by player: ${player} in room: ${room}`);
            room.addPlayerQuestion(player, question);
        } else {
            console.log(`asking computer question: ${question} in room: ${room}`);
            room.addComputerQuestion(question)
        }

        if (room.isCurrentRoundFullyQuestioned()) {
            this.emitForRoomPlayers(room, BaseGameEvents.ROOM_UPDATE, room);
        }
    }

    abstract createComputerQuestion(): Question | undefined;

    protected createAndAddComputerQuestion(room: GameRoom) {
        const question = this.createComputerQuestion();
        this.addQuestion(room, question, undefined);
    }

    abstract createPlayerQuestion(...args: any[]): Question | undefined;

    createAndAddPlayerQuestion(player: User, ...args: any[]) {
        const room = this.getPlayerRoom(player);
        const question = this.createPlayerQuestion(...args);
        this.addQuestion(room, question, player);
    }
}
