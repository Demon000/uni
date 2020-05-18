import '../css/ajax_1.css';

import Vue from 'vue';

const useXHR = true;

const app = new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        cities: [],
        selectedCity: null,
        connections: [],
    },
    mounted() {
        this.loadCities();
    },
    methods: {
        loadCities() {
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('GET', '/api/cities', true);
                req.onload = () => {
                    this.cities = req.response;
                };
                req.onerror = () => {
                    console.error('Failed to retrieve cities');
                };
                req.send();
            }
        },
        loadConnections(city) {
            this.connections = [];
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('GET', `/api/cities/${city.id}`, true);
                req.onload = () => {
                    this.connections = req.response.connections;
                };
                req.onerror = () => {
                    console.error('Failed to retrieve city connections');
                };
                req.send();
            }
        },
        onCityClick(city) {
            if (this.selectedCity !== city) {
                this.selectedCity = city;
                this.loadConnections(city);
            } else {
                this.selectedCity = null;
            }
        },
    },
});
