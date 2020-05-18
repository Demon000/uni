import '../css/ajax_4.css';

import Vue from 'vue';
import Request from "./Request";

new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        table: [],
        letters: ['X', '0'],
        state: null,
    },
    mounted() {
        this.shuffle(this.letters);
    },
    methods: {
        shuffle(a) {
            for (let i = a.length - 1; i > 0; i--) {
                const j = Math.floor(Math.random() * (i + 1));
                [a[i], a[j]] = [a[j], a[i]];
            }
            return a;
        },
        toGameLetter(cell) {
            if (cell === 'empty') {
                return '';
            } else if (cell === 'user') {
                return this.letters[0];
            } else if (cell === 'computer') {
                return this.letters[1];
            }
        },
        updateData(data) {
            this.table = data.table;
            this.state = data.state;
        },
        async onStartClick() {
            let response;
            try {
                response = await Request.post('/api/tic_tac_toe/start');
            } catch (e) {
                console.error(e);
                return;
            }


            this.updateData(response);
        },
        async onCellClick(rowIndex, columnIndex) {
            let response;
            try {
                response = await Request.post('/api/tic_tac_toe/play', {
                    move: [rowIndex, columnIndex],
                });
            } catch (e) {
                console.error(e);
                return;
            }


            this.updateData(response);
        },
    },
});
