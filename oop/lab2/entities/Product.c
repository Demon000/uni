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

char* Product__get_str(Product* product) {
    char* str = malloc(sizeof(char) * PRODUCT_REPRESENTATION_MAX_SIZE);

    sprintf(str, "Id: %d, Type: %s, Brand: %s, Model: %s, "
            "Price: %d, Amount %d\n", product->id,
            product->type, product->brand, product->model,
            product->price, product->amount);

    return str;
}

void Product__free_str(char* str) {
    free(str);
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
