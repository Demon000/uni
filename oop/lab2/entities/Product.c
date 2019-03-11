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

void Product__destroy(Product* product) {
    free(product);
}

void Product__set_price(Product* product, int price) {
    product->price = price;
}

void Product__set_amount(Product* product, int amount) {
    product->amount = amount;
}

ProductsList* ProductsList__create(int length) {
    ProductsList* list = malloc(sizeof(ProductsList));
    list->items = malloc(sizeof(Product*) * length);
    return list;
}

void ProductsList__destroy(ProductsList* list) {
    free(list->items);
    free(list);
}

int ProductsList__get_length(ProductsList* list) {
    return list->length;
}

Product* ProductsList__get(ProductsList* list, int i) {
    if (i >= list->length) {
        return NULL;
    }

    return list->items[i];
}

void ProductsList__swap(ProductsList* list, int first, int second) {
    if (first < 0 || first >= list->length ||
            second < 0 || second >= list->length) {
        return;
    }

    Product* aux = list->items[first];
    list->items[first] = list->items[second];
    list->items[second] = aux;
}
