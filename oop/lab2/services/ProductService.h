#include "../entities/Product.h"
#include "../repositories/ProductRepository.h"

#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

typedef struct ProductService {
    ProductRepository* repository;
} ProductService;

typedef enum ProductSortType {
    SORT_BY_PRICE,
    SORT_BY_AMOUNT,
} ProductSortType;

typedef enum ProductSortOrder {
    SORT_ASCENDING,
    SORT_DESCENDING,
} ProductSortOrder;

ProductService* ProductService__create(ProductRepository*);
void ProductService__destroy(ProductService*);

Product* ProductService__add_product(ProductService*, ProductId, ProductPrice, ProductAmount, char*, char*, char*);
void ProductService__remove_product(ProductService*, ProductId);
Product* ProductService__update_product(ProductService*, ProductId, ProductPrice, ProductAmount);

ProductsList* ProductService__get_sorted_products(ProductService*, ProductSortType, ProductSortOrder);
ProductsList* ProductService__get_products(ProductService*);
ProductsList* ProductService__get_products_by_brand(ProductService*, char*);
ProductsList* ProductService__get_products_by_price(ProductService*, ProductPrice);
ProductsList* ProductService__get_products_by_amount(ProductService*, ProductAmount);

#endif // PRODUCT_SERVICE_H
