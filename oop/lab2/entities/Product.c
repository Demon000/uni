#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Product.h"

Product* Product__create(ProductId id,
        ProductPrice price, ProductAmount amount,
        char* type, char* brand, char* model) {
    Product *product = malloc(sizeof(Product));
    product->id = id;
    product->price = price;
    product->amount = amount;

    strcpy(product->type, type);
    strcpy(product->brand, brand);
    strcpy(product->model, model);

    return product;
}

ProductId Product__get_id(Product* product) {
    return product->id;
}

ProductPrice Product__get_price(Product* product) {
    return product->price;
}

ProductAmount Product__get_amount(Product* product) {
    return product->amount;
}

char* Product__get_type(Product* product) {
    return product->type;
}

char* Product__get_brand(Product* product) {
    return product->brand;
}

char* Product__get_model(Product* product) {
    return product->model;
}

void Product__set_price(Product* product, int price) {
    product->price = price;
}

void Product__set_amount(Product* product, int amount) {
    product->amount = amount;
}

void Product__destroy(Product* product) {
    free(product);
}
