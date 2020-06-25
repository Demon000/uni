<template>
    <div>
        <div>
            Logged in as {{ user.username }}.
        </div>

        <div v-if="!room">
            Waiting for initial room state...
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
        <div v-else-if="room.status === 'WAITING_FOR_ANSWERS'">
            Waiting for answers...
            Round: {{room.round + 1}} / {{room.neededNoRounds}}

            <div v-for="question in getCurrentRoundQuestions()" v-bind:key="question.id">
                Letter: {{question.letter}}

                <div>
                    <label>Country</label>
                    <input type="text" v-model="getAnswerForQuestion(question).country">
                </div>

                <div>
                    <label>City</label>
                    <input type="text" v-model="getAnswerForQuestion(question).city">
                </div>

                <div>
                    <label>Mountain</label>
                    <input type="text" v-model="getAnswerForQuestion(question).mountain">
                </div>

                <button v-on:click="addPlayerAnswer(question)">ANSWER</button>
            </div>
        </div>
        <div v-else-if="room.status === 'WAITING_FOR_ROUND_END'">
            Waiting for round end...
        </div>
        <div v-else-if="room.status === 'ENDED'">
            Game ended!
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
    import {QuestionType} from '../../common/game/QuestionType';
    import IQuestion from '../../common/domain/IQuestion';
    import IAnswer from '../../common/domain/IAnswer';
    import Answer from '../../common/domain/Answer';

    @Component
    export default class Game extends Vue {
        room: IGameRoomState = {
            neededNoPlayers: 0,
            neededNoRounds: 0,
            questionType: QuestionType.COMPUTER_GENERATED,
            status: GameRoomStatus.WAITING_FOR_PLAYERS,
            players: [],
            questions: [],
            answers: [],
            round: 0,
        };
        answers: {[x: number]: IAnswer} = [];

        private _gameService!: IGameService;

        mounted() {
            const socket = io('/tom');
            this._gameService = new ClientSocketGameService(socket);

            this._gameService.on(GameServiceEvents.ROOM_UPDATE, (room: IGameRoomState) => {
                this.onRoomUpdate(room);
            })
        }

        private onRoomUpdate(room: IGameRoomState) {
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

        get user(): ISafeUser | undefined {
            return store.state.user;
        }

        getCurrentRoundQuestions() {
            if (!this.room) {
                return;
            }

            return this.room.questions.filter(question => question.round == this.room.round);
        }

        startRoom() {
            if (!this.user) {
                return;
            }

            this._gameService.startRoom(this.user);
        }
    }
</script>

<style scoped>

</style>
