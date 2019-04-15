#include <stdlib.h>
#include <string.h>

#include "ProductRepository.h"

ProductRepository* ProductRepository__create() {
    ProductRepository* repository =
            malloc(sizeof(ProductRepository));

    repository->products = Vector__create();

    return repository;
}

void ProductRepository__add_product(ProductRepository* repository,
        Product* product) {
    Vector__add(repository->products, product);
}

Product* ProductRepository__get_product_by_id(ProductRepository* repository,
        ProductId id) {
    int length = Vector__get_length(repository->products);
    Product* product;
    int i;

    for (i = 0; i < length; i++) {
        product = Vector__get(repository->products, i);
        if (product->id == id) {
            break;
        }
    }

    if (i < length) {
        return product;
    }

    return NULL;
}

#define GET_PRODUCTS_LIST(condition) \
        int length = Vector__get_length(repository->products); \
        Vector* products = Vector__create(length); \
        Product* product; \
        for (int i = 0; i < length; i++) { \
            product = Vector__get(repository->products, i); \
            if (condition) { \
                Vector__add(products, product); \
            } \
        } \
        return products; \

Vector* ProductRepository__get_products(ProductRepository* repository) {
    GET_PRODUCTS_LIST(1)
}

Vector* ProductRepository__get_products_by_brand(
        ProductRepository* repository, char* brand) {
    GET_PRODUCTS_LIST(strcmp(product->brand, brand) == 0)
}

Vector* ProductRepository__get_products_by_price(
        ProductRepository* repository, ProductPrice price) {
    GET_PRODUCTS_LIST(product->price == price)
}

Vector* ProductRepository__get_products_by_amount(
        ProductRepository* repository, ProductAmount amount) {
    GET_PRODUCTS_LIST(product->amount == amount)
}

void ProductRepository__update_product(ProductRepository* repository,
        Product* product, ProductPrice price, ProductAmount amount) {
    (void)(repository);
    if (price != -1) {
        Product__set_price(product, price);
    }

    if (amount != -1) {
        Product__set_amount(product, amount);
    }
}

void ProductRepository__remove_product(
        ProductRepository* repository, Product* product) {
    int length = Vector__get_length(repository->products);
    int i;

    for (i = 0; i < length; i++) {
        Product* aux_product = Vector__get(repository->products, i);
        if (aux_product == product) {
            break;
        }
    }

    if (i < length) {
        Vector__delete(repository->products, i);
        return;
    }

    return;
}

void ProductRepository__destroy(ProductRepository* repository) {
    Vector__destroy(repository->products);

    free(repository);
}
