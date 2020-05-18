import '../css/ajax_6.css';

import Vue from 'vue';
import Request from "./Request";

new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        products: [],
        attributes: [],
    },
    async mounted() {
        await this.loadProducts();
        await this.loadAttributes();
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
        async loadAttributes() {
            let response;
            try {
                response = await Request.get('/api/products/attributes');
            } catch (e) {
                console.error(e);
                return;
            }

            this.setAttributes(response);
        },
        async loadProducts() {
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

            let response;
            try {
                response = await Request.get(`/api/products${queryString}`);
            } catch (e) {
                console.error(e);
                return;
            }


            this.products = response;
        },
    },
});
