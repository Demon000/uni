#include <stdlib.h>

#include "ProductService.h"

ProductService* ProductService__create(ProductRepository* repository) {
    ProductService* service = malloc(sizeof(ProductService));

    service->repository = repository;
}

void ProductService__destroy(ProductService* service) {
    free(service);
}

Product* ProductService__add_product(ProductService* service,
        ProductId id, ProductPrice price, ProductAmount amount,
        char* type, char* brand, char* model) {
    Product* existing_product = ProductRepository__get_product_by_id(service->repository, id);

    if (existing_product) {
        Product__set_amount(existing_product, amount);
        return existing_product;
    }

    Product* product = Product__create(id, price, amount, type, brand, model);
    ProductRepository__add_product(service->repository, product);

    return product;
}

void ProductService__remove_product(ProductService* service, ProductId id) {
    Product* product = ProductRepository__get_product_by_id(service->repository, id);
    if (!product) {
        return;
    }

    ProductRepository__remove_product(service->repository, product);
    Product__destroy(product);
}

ProductsList* ProductService__get_products(ProductService* service) {
    ProductsList* list = ProductRepository__get_products(service->repository);
    return list;
}

ProductsList* ProductService__get_products_by_brand(ProductService* service, char* brand) {

}

ProductsList* ProductService__get_products_by_price(ProductService* service, ProductPrice price) {

}

ProductsList* ProductService__get_products_by_amount(ProductService* service, ProductAmount amount) {

}
