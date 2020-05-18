import '../css/ajax_3.css';

import Vue from 'vue';

const useXHR = true;

const app = new Vue({
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
    mounted() {
        this.loadProducts();
    },
    methods: {
        loadProducts() {
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('GET', `/api/products`, true);
                req.onload = () => {
                    this.products = req.response;
                };
                req.onerror = () => {
                    console.error('Failed to retrieve products');
                };
                req.send();
            }
        },
        updateProduct(id, data) {
            if (useXHR) {
                const req = new XMLHttpRequest();
                req.responseType = 'json';
                req.open('PATCH', `/api/products/${id}`, true);
                req.onload = () => {
                    this.loadProducts();
                    this.selectProduct(null);
                };
                req.onerror = () => {
                    console.error('Failed to update product');
                };
                req.setRequestHeader('Content-Type', 'application/json');
                req.send(JSON.stringify(data));
            }
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
        onSaveClick() {
            this.updateProduct(this.selectedProduct.id, {
                name: this.productName,
                description: this.productDescription,
                price: this.productPrice,
            });
        },
    },
});
