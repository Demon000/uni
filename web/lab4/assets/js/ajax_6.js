import '../css/ajax_6.css';

import Vue from 'vue';

const useXHR = true;

const app = new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        products: [],
        attributes: [],
    },
    mounted() {
        this.loadProducts();
        this.loadAttributes();
    },
    filters: {
        capitalize: function (value) {
            if (!value) return '';
            value = value.toString();
            return value.charAt(0).toUpperCase() + value.slice(1);
        }
    },
    methods: {
        setAttributes(attributes) {
            for (const attribute of Object.values(attributes)) {
                attribute.value = '';
            }

            this.attributes = attributes;
        },
        loadAttributes() {
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('GET', `/api/products/attributes`, true);
                req.onload = () => {
                    if (req.response.error) {
                        console.error(req.response.message);
                        return;
                    }

                    this.setAttributes(req.response);

                };
                req.onerror = () => {
                    console.error('Failed to retrieve attributes');
                };
                req.send();
            }
        },
        loadProducts() {
            let queryString = '';

            for (const attribute of Object.values(this.attributes)) {
                if (!attribute.value) {
                    continue;
                }

                if (queryString !== '') {
                    queryString += '&';
                }

                queryString += `${attribute.name}=${attribute.value}`;
            }

            if (queryString) {
                queryString = '?' + queryString;
            }

            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('GET', `/api/products${queryString}`, true);
                req.onload = () => {
                    if (req.response.error) {
                        console.error(req.response.message);
                        return;
                    }

                    this.products = req.response;
                };
                req.onerror = () => {
                    console.error('Failed to retrieve attributes');
                };
                req.send();
            }
        },
    },
});
