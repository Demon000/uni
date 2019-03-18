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

ProductsList* ProductService__get_products(ProductService* service) {
    ProductsList* list = ProductRepository__get_products(service->repository);
    return list;
}

int ProductService__compare_products_price(Product* first, Product* second) {
    return second->price - first->price;
}

int ProductService__compare_products_amount(Product* first, Product* second) {
    return second->amount - first->amount;
}

int ProductService__compare_products_price_desc(Product* first, Product* second) {
    return first->price - second->price;
}

int ProductService__compare_products_amount_desc(Product* first, Product* second) {
    return first->amount - second->amount;
}

ProductsList* ProductService__get_sorted_products(ProductService* service,
        ProductSortType type, ProductSortOrder order) {
    ProductsList* list = ProductRepository__get_products(service->repository);

    if (type == SORT_BY_PRICE) {
        if (order == SORT_ASCENDING) {
            ProductsList__sort(list, ProductService__compare_products_price);
        } else if (order == SORT_DESCENDING) {
            ProductsList__sort(list, ProductService__compare_products_price_desc);
        }
    } else if (type == SORT_BY_AMOUNT) {
        if (order == SORT_ASCENDING) {
            ProductsList__sort(list, ProductService__compare_products_amount);
        } else if (order == SORT_DESCENDING) {
            ProductsList__sort(list, ProductService__compare_products_amount_desc);
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
    ProductsList* list = ProductRepository__get_products(service->repository);

    int length = ProductsList__get_length(list);
    for (int i = 0; i < length; i++) {
        Product* product = ProductsList__get(list, i);
        Product__destroy(product);
    }

    ProductsList__destroy(list);

    free(service);
}
