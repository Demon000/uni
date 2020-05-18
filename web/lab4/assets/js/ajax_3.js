import '../css/ajax_3.css';

import Vue from 'vue';
import Request from "./Request";

new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    data: {
        products: [],
        selectedProduct: null,
        productName: '',
        productDescription: '',
        productPrice: 0,
    },
    computed: {
        changed() {
            if (!this.selectedProduct) {
                return false;
            }

            return this.selectedProduct.name !== this.productName ||
                this.selectedProduct.description !== this.productDescription ||
                this.selectedProduct.price !== this.productPrice;
        }
    },
    async mounted() {
        await this.loadProducts();
    },
    methods: {
        async loadProducts() {
            let response;

            try {
                response = await Request.get('/api/products');
            } catch (e) {
                console.error(e);
                return;
            }

            this.products = response;
        },
        async updateProduct(id, data) {
            try {
                await Request.patch(`/api/products/${id}`, data);
            } catch (e) {
                console.error(e);
                return;
            }

            await this.loadProducts();
            await this.selectProduct();
        },
        selectProduct(product) {
            if (product) {
                this.productName = product.name;
                this.productDescription = product.description;
                this.productPrice = product.price;
            }
            this.selectedProduct = product;
        },
        onProductClick(product) {
            if (this.changed) {
                const ignoreChanges = window.confirm("Product has changes, are you sure you want to switch?");
                if (!ignoreChanges) {
                    return;
                }
            }
            if (this.selectedProduct !== product) {
                this.selectProduct(product);
            } else {
                this.selectProduct(null);
            }
        },
        async onSaveClick() {
            await this.updateProduct(this.selectedProduct.id, {
                name: this.productName,
                description: this.productDescription,
                price: this.productPrice,
            });
        },
    },
});
