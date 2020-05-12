import API from './API';
import ArbitersResource from "./ArbitersResource";
import RacesResource from "./RacesResource";
import Vue from 'vue';

const api = new API('http://localhost', 8080);
const arbitersResource = new ArbitersResource(api);
const racesResource = new RacesResource(api);

new Vue({
    el: '#app',
    data: {
        races: [],
        selectedRace: null,
        newRace: {
            name: '',
            arbiter: {
                id: '',
            },
        },
        arbiters: [],
    },
    async mounted() {
        await this.loadArbiters();
        await this.loadRaces();
    },
    methods: {
        async loadArbiters() {
            try {
                this.arbiters = await arbitersResource.find();
            } catch (e) {
                console.error(e);
            }
        },
        async loadRaces() {
            try {
                this.races = await racesResource.find();
            } catch (e) {
                console.error(e);
            }
        },
        onRaceClick(race) {
            if (this.selectedRace && this.selectedRace.id === race.id) {
                this.selectedRace = null;
            } else {
                this.selectedRace = race;
            }
        },
        async onNewRaceClick() {
            this.onRaceClick(this.newRace);
        },
        async onCreateRaceClick() {
            try {
                await racesResource.add(this.newRace);
                await this.loadRaces()
            } catch (e) {
                console.error(e);
            }
        },
        async onUpdateRaceClick() {
            try {
                await racesResource.update(this.selectedRace);
                await this.loadRaces()
            } catch (e) {
                console.error(e);
            }
        },
        async onDeleteRaceClick() {
            try {
                await racesResource.delete(this.selectedRace.id);
                await this.loadRaces()
            } catch (e) {
                console.error(e);
            }
        },
    }
});
