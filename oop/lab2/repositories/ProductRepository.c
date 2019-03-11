#include <stdlib.h>

#include "ProductRepository.h"

ProductRepository* ProductRepository__create() {
    ProductRepository* repository =
            malloc(sizeof(ProductRepository));

    repository->products = Vector__create();
}

void ProductRepository__destroy(ProductRepository* repository) {
    Vector__destroy(repository->products);

    free(repository);
}

void ProductRepository__add_product(ProductRepository* repository, Product* product) {
    Vector__add(repository->products, product);
}
void ProductRepository__remove_product(ProductRepository* repository, Product* product) {
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

Product* ProductRepository__get_product_by_id(ProductRepository* repository, ProductId id) {
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

ProductsList* ProductRepository__get_products(ProductRepository* repository) {
    int length = Vector__get_length(repository->products);
    ProductsList* list = ProductsList__create(length);
    Product* product;
    int index = 0;

    for (int i = 0; i < length; i++) {
        product = Vector__get(repository->products, i);
        list->items[index++] = product;
    }

    list->length = index;

    return list;
}

ProductsList* ProductRepository__get_products_by_brand(ProductRepository* repository, char* brand) {

}

ProductsList* ProductRepository__get_products_by_price(ProductRepository* repository, ProductPrice price) {

}

ProductsList* ProductRepository__get_products_by_amount(ProductRepository* repository, ProductAmount amount) {

}

void ProductRepository__free_products(ProductsList* list) {
    ProductsList__destroy(list);
}
