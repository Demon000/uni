import '../css/ajax_2.css';

import Vue from 'vue';
import Request from "./Request";

new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        people: [],
        page: 0,
        before: 0,
        after: 0,
        loading: false,
    },
    async mounted() {
        await this.loadPeople();
    },
    methods: {
        async loadPeople() {
            this.loading = true;

            let response;
            try {
                response = await Request.get(`/api/people?page=${this.page}`);
            } catch (e) {
                console.error(e);
                return;
            }

            this.people = response.data;
            this.before = response.before;
            this.after = response.after;
            this.loading = false;
        },
        async nextPage() {
            this.page++;
            await this.loadPeople();
        },
        async prevPage() {
            this.page--;
            await this.loadPeople();
        },
    },
});
