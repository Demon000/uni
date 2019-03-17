#include <stdlib.h>

#include "ProductService.h"

ProductService* ProductService__create(ProductRepository* repository) {
    ProductService* service = malloc(sizeof(ProductService));

    service->repository = repository;
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

ProductsList* ProductService__get_products(ProductService* service) {
    ProductsList* list = ProductRepository__get_products(service->repository);
    return list;
}

ProductsList* ProductService__get_sorted_products(ProductService* service,
        ProductSortType type, ProductSortOrder order) {
    ProductsList* list = ProductRepository__get_products(service->repository);
    int length = ProductsList__get_length(list);
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            Product* first = ProductsList__get(list, i);
            Product* second = ProductsList__get(list, j);
            int value;

            if (type == SORT_BY_PRICE) {
                value = second->price - first->price;
            } else if (type == SORT_BY_AMOUNT) {
                value = second->amount - first->amount;
            }

            if (order == SORT_DESCENDING) {
                value = -value;
            }

            if (value < 0) {
                ProductsList__swap(list, i, j);
            }
        }
    }

    return list;
}

ProductsList* ProductService__get_products_by_brand(ProductService* service,
        char* brand) {
    ProductsList* list = ProductRepository__get_products_by_brand(
            service->repository, brand);
    return list;
}

ProductsList* ProductService__get_products_by_price(ProductService* service,
        ProductPrice price) {
    ProductsList* list = ProductRepository__get_products_by_price(
            service->repository, price);
    return list;
}

ProductsList* ProductService__get_products_by_amount(ProductService* service,
        ProductAmount amount) {
    ProductsList* list = ProductRepository__get_products_by_amount(
            service->repository, amount);
    return list;
}

Product* ProductService__update_product(ProductService* service,
        ProductId id, ProductPrice price, ProductAmount amount) {
    Product* product = ProductRepository__get_product_by_id(service->repository, id);
    if (!product) {
        return NULL;
    }

    ProductRepository__update_product(service->repository, product, price, amount);
    return product;
}

ProductError ProductService__remove_product(ProductService* service, ProductId id) {
    Product* product = ProductRepository__get_product_by_id(service->repository, id);
    if (!product) {
        return PRODUCT_NOT_FOUND;
    }

    ProductRepository__remove_product(service->repository, product);
    Product__destroy(product);

    return PRODUCT_NO_ERROR;
}

void ProductService__destroy(ProductService* service) {
    ProductsList* list = ProductRepository__get_products(service->repository);

    int length = ProductsList__get_length(list);
    for (int i = 0; i < length; i++) {
        Product* product = ProductsList__get(list, i);
        Product__destroy(product);
    }

    ProductsList__destroy(list);

    free(service);
}
