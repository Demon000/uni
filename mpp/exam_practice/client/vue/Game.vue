<template>
    <div>
        <div>
            Logged in as {{ user.username }}.
        </div>

        <div v-if="room.status === 'UNKNOWN'">
            You didn't join any room!
            <button v-on:click="joinRoom">Join room</button>
        </div>
        <div v-else-if="room.status === 'WAITING_FOR_PLAYERS'">
            Waiting for players...
            {{ room.players.length }} / {{ room.neededNoPlayers }}
        </div>
        <div v-else-if="room.status === 'WAITING_TO_START'">
            Waiting to start...
            <button v-on:click="startRoom">Start</button>
        </div>
        <div v-else-if="room.status === 'WAITING_FOR_QUESTIONS'">
            Waiting for questions...
        </div>
        <div v-else-if="room.status === 'WAITING_FOR_ANSWERS' || room.status === 'WAITING_FOR_EVERYONE_TO_ANSWER'
                || room.status === 'ENDED'">
            <div v-if="room.status === 'ENDED'">
                Game ended!
                Winner is {{ getUsername(room.winner.username) }}
            </div>
            <div v-else-if="room.status === 'WAITING_FOR_EVERYONE_TO_ANSWER'">
                Waiting for other people to answer...
            </div>
            <div v-else-if="room.status === 'WAITING_FOR_ANSWERS'">
                Waiting for answer...
            </div>

            <div>
                Round: {{room.round + 1}} / {{room.neededNoRounds}}
            </div>

            <div>
                Current configuration:
                <div>
                    <div class="configuration-item" v-for="configurationItem in question.configuration">
                        {{ getUsername(configurationItem) }}
                    </div>
                </div>
            </div>

            <div v-if="room.status === 'WAITING_FOR_ANSWERS'">
                Press the button bellow to roll a random number of steps between 1 and 4:
                <button v-on:click="rollRandomAnswer(question)">ROLL</button>
            </div>
            <div v-else-if="room.status === 'WAITING_FOR_EVERYONE_TO_ANSWER'">
                You rolled: {{ getAnswerForQuestion(question).roll }}
                Waiting for everyone else to roll.
            </div>
            <div v-else-if="room.status === 'ENDED'">
                Replay?
                <button v-on:click="leaveJoinRoom">Replay</button>
            </div>

            <table class="answers-table" v-if="room.answers.length">
                <tr>
                    <th>Username</th>
                    <th>Roll</th>
                    <th>Round</th>
                </tr>
                <tr v-for="answer in room.answers">
                    <td>
                        {{ getUsername(answer.player.username) }}
                    </td>
                    <td>
                        {{ answer.roll }}
                    </td>
                    <td>
                        {{ answer.round + 1 }}
                    </td>
                </tr>
            </table>
        </div>
    </div>
</template>

<script lang="ts">
    import io from 'socket.io-client';
    import {Component, Vue} from 'vue-property-decorator';

    import {IGameRoomState} from '../../common/domain/IGameRoomState';
    import {GameServiceEvents, IGameService} from '../../common/service/IGameService';
    import {GameRoomStatus} from '../../common/game/GameRoomStatus';

    import store from '../ts/store';
    import ClientSocketGameService from '../ts/ClientSocketGameService';
    import ISafeUser from '../../common/domain/ISafeUser';
    import IQuestion from '../../common/domain/IQuestion';
    import IAnswer from '../../common/domain/IAnswer';
    import Answer from '../../common/domain/Answer';

    function getRandomInRange(min: number, max: number): number {
        return Math.floor(Math.random() * (max - min) + min);
    }

    @Component
    export default class Game extends Vue {
        room: IGameRoomState = {
            neededNoPlayers: 0,
            neededNoRounds: 0,
            status: GameRoomStatus.UNKNOWN,
            players: [],
            originalConfiguration: [],
            questions: [],
            answers: [],
            round: 0,
            winner: undefined,
        };
        answers: {[x: number]: IAnswer} = [];

        private _gameService!: IGameService;

        mounted() {
            const socket = io('/tom', {
                transports: ['websocket'],
                upgrade: false,
            });
            this._gameService = new ClientSocketGameService(socket);

            this._gameService.on(GameServiceEvents.ROOM_UPDATE, (room: IGameRoomState) => {
                this.onRoomUpdate(room);
            })
        }

        private onRoomUpdate(room: IGameRoomState) {
            console.log(room);
            this.room = room;
        }

        private getAnswerForQuestion(question: IQuestion) {
            if (!(question.id in this.answers)) {
                this.answers[question.id] = new Answer();
            }

            return this.answers[question.id];
        }

        private addPlayerAnswer(question: IQuestion) {
            if (!this.user) {
                return;
            }

            const answer = this.getAnswerForQuestion(question);
            this._gameService.createAndAddPlayerAnswer(this.user, question.id, answer);
        }

        private rollRandomAnswer(question: IQuestion) {
            if (!this.user) {
                return;
            }

            const roll = getRandomInRange(1, 5);
            const answer = this.getAnswerForQuestion(question);
            answer.roll = roll;
            this._gameService.createAndAddPlayerAnswer(this.user, question.id, answer);
        }

        getUsername(username: string) {
            if (!this.user) {
                return username;
            }

            if (username === this.user.username) {
                return 'you';
            } else {
                return username;
            }
        }

        get user(): ISafeUser | undefined {
            return store.state.user;
        }

        get question() {
            if (!this.room) {
                return;
            }

            return this.room.questions.find(question => question.round == this.room.round);
        }

        startRoom() {
            if (!this.user) {
                return;
            }

            this._gameService.startRoom(this.user);
        }

        joinRoom() {
            if (!this.user) {
                return;
            }

            this._gameService.joinRoom(this.user);
        }

        leaveRoom() {
            if (!this.user) {
                return;
            }

            this._gameService.leaveRoom(this.user);
        }

        leaveJoinRoom() {
            this.leaveRoom();
            this.joinRoom();
        }
    }
</script>

<style scoped>
.configuration-item {
    display: inline-block;

    padding: 8px;
    border: 1px solid black;
}
.answers-table {
    border: 1px solid black;
}
</style>
