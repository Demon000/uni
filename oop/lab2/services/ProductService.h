#include "../entities/Product.h"
#include "../repositories/ProductRepository.h"

#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

typedef struct ProductService {
    ProductRepository* product_repository;
} ProductService;

ProductService* ProductService__create(ProductRepository*);
void ProductService__destroy(ProductService*);

void ProductService__add_product(ProductService*, ProductId, ProductPrice, ProductAmount, char*, char*, char*);
void ProductService__remove_product(ProductService*, ProductId);

Product** ProductService__get_products(ProductService*);
Product** ProductService__get_products_by_brand(ProductService*, char*);
Product** ProductService__get_products_by_price(ProductService*, int);
Product** ProductService__get_products_by_amount(ProductService*, int);
Product* ProductService__get_product_by_id(ProductService*, ProductId);

#endif // PRODUCT_SERVICE_H
