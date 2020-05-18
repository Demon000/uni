import '../css/ajax_1.css';

import Vue from 'vue';
import Request from './Request';

new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        cities: [],
        selectedCity: null,
        connections: [],
    },
    async mounted() {
        await this.loadCities();
    },
    methods: {
        async loadCities() {
            let response;
            try {
                response = await Request.get(`/api/cities`);
            } catch (e) {
                console.error(e);
                return;
            }

            this.cities = response;
        },
        async loadConnections(city) {
            this.connections = [];

            let response;
            try {
                response = await Request.get(`/api/cities/${city.id}`);
            } catch (e) {
                console.error(e);
                return;
            }

            this.connections = response.connections;
        },
        async onCityClick(city) {
            if (this.selectedCity !== city) {
                this.selectedCity = city;
                await this.loadConnections(city);
            } else {
                this.selectedCity = null;
            }
        },
    },
});
