import '../css/ajax_2.css';

import Vue from 'vue';

const useXHR = true;

const app = new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        people: [],
        page: 0,
        before: 0,
        after: 0,
        loading: false,
    },
    mounted() {
        this.loadPeople();
    },
    methods: {
        loadPeople() {
            this.loading = true;
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('GET', `/api/people?page=${this.page}`, true);
                req.onload = () => {
                    this.people = req.response.data;
                    this.before = req.response.before;
                    this.after = req.response.after;
                    this.loading = false;
                };
                req.onerror = () => {
                    console.error('Failed to retrieve people');
                };
                req.send();
            }
        },
        nextPage() {
            this.page++;
            this.loadPeople();
        },
        prevPage() {
            this.page--;
            this.loadPeople();
        },
    },
});
