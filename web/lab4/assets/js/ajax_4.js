import '../css/ajax_4.css';

import Vue from 'vue';

const useXHR = true;

const app = new Vue({
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
        onStartClick() {
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('POST', `/api/tic_tac_toe/start`, true);
                req.onload = () => {
                    if (req.response.error) {
                        console.error(req.response.message);
                        return;
                    }

                    this.updateData(req.response);
                };
                req.onerror = () => {
                    console.error('Failed to update table');
                };
                req.send();
            }
        },
        onCellClick(rowIndex, columnIndex) {
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('POST', `/api/tic_tac_toe/play`, true);
                req.onload = () => {
                    if (req.response.error) {
                        console.error(req.response.message);
                        return;
                    }

                    this.updateData(req.response);

                };
                req.onerror = () => {
                    console.error('Failed to update table');
                };
                req.setRequestHeader('Content-Type', 'application/json');
                req.send(JSON.stringify({
                    move: [rowIndex, columnIndex],
                }));
            }
        },
    },
});
