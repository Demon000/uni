#include "../entities/Product.h"
#include "../repositories/ProductRepository.h"

#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

typedef struct ProductService {
    ProductRepository* repository;
} ProductService;

ProductService* ProductService__create(ProductRepository*);
void ProductService__destroy(ProductService*);

Product* ProductService__add_product(ProductService*, ProductId, ProductPrice, ProductAmount, char*, char*, char*);
void ProductService__remove_product(ProductService*, ProductId);

Product** ProductService__get_products(ProductService*);
Product** ProductService__get_products_by_brand(ProductService*, char*);
Product** ProductService__get_products_by_price(ProductService*, ProductPrice);
Product** ProductService__get_products_by_amount(ProductService*, ProductAmount);

#endif // PRODUCT_SERVICE_H
