#include <stdlib.h>

#include "ProductService.h"

ProductService* ProductService__create(ProductRepository* repository) {
    ProductService* service = malloc(sizeof(ProductService));

    service->repository = repository;

    return service;
}

Product* ProductService__add_product(ProductService* service,
        ProductId id, ProductPrice price, ProductAmount amount,
        char* type, char* brand, char* model) {
    Product* existing_product =
            ProductRepository__get_product_by_id(service->repository, id);

    if (existing_product) {
        Product__set_amount(existing_product, amount);
        return existing_product;
    }

    Product* product = Product__create(id, price, amount, type, brand, model);
    ProductRepository__add_product(service->repository, product);

    return product;
}

Vector* ProductService__get_products(ProductService* service) {
    Vector* products = ProductRepository__get_products(service->repository);
    return products;
}

int ProductService__compare_products_price(void* first, void* second) {
    Product* first_product = (Product*) first;
    Product* second_product = (Product*) second;
    return second_product->price - first_product->price;
}

int ProductService__compare_products_amount(void* first, void* second) {
    Product* first_product = (Product*) first;
    Product* second_product = (Product*) second;
    return second_product->amount - first_product->amount;
}

int ProductService__compare_products_price_desc(void* first, void* second) {
    Product* first_product = (Product*) first;
    Product* second_product = (Product*) second;
    return first_product->price - second_product->price;
}

int ProductService__compare_products_amount_desc(void* first, void* second) {
    Product* first_product = (Product*) first;
    Product* second_product = (Product*) second;
    return first_product->amount - second_product->amount;
}

Vector* ProductService__get_sorted_products(ProductService* service,
        ProductSortType type, ProductSortOrder order) {
    Vector* products = ProductRepository__get_products(service->repository);

    if (type == SORT_BY_PRICE) {
        if (order == SORT_ASCENDING) {
            Vector__sort(products, ProductService__compare_products_price);
        } else if (order == SORT_DESCENDING) {
            Vector__sort(products, ProductService__compare_products_price_desc);
        }
    } else if (type == SORT_BY_AMOUNT) {
        if (order == SORT_ASCENDING) {
            Vector__sort(products, ProductService__compare_products_amount);
        } else if (order == SORT_DESCENDING) {
            Vector__sort(products, ProductService__compare_products_amount_desc);
        }
    }

    return products;
}

Vector* ProductService__get_products_by_brand(ProductService* service,
        char* brand) {
    Vector* products = ProductRepository__get_products_by_brand(
            service->repository, brand);
    return products;
}

Vector* ProductService__get_products_by_price(ProductService* service,
        ProductPrice price) {
    Vector* products = ProductRepository__get_products_by_price(
            service->repository, price);
    return products;
}

Vector* ProductService__get_products_by_amount(ProductService* service,
        ProductAmount amount) {
    Vector* products = ProductRepository__get_products_by_amount(
            service->repository, amount);
    return products;
}

Product* ProductService__update_product(ProductService* service,
        ProductId id, ProductPrice price, ProductAmount amount) {
    Product* product =
            ProductRepository__get_product_by_id(service->repository, id);
    if (!product) {
        return NULL;
    }

    ProductRepository__update_product(service->repository,
            product, price, amount);
    return product;
}

ProductError ProductService__remove_product(ProductService* service,
        ProductId id) {
    Product* product =
            ProductRepository__get_product_by_id(service->repository, id);
    if (!product) {
        return PRODUCT_NOT_FOUND;
    }

    ProductRepository__remove_product(service->repository, product);
    Product__destroy(product);

    return PRODUCT_NO_ERROR;
}

void ProductService__destroy(ProductService* service) {
    Vector* products = ProductRepository__get_products(service->repository);

    int length = Vector__get_length(products);
    for (int i = 0; i < length; i++) {
        Product* product = Vector__get(products, i);
        Product__destroy(product);
    }

    Vector__destroy(products);

    free(service);
}
