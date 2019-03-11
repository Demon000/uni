#include "../entities/Product.h"
#include "../repositories/ProductRepository.h"

#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

struct ProductService {
    struct ProductRepository* product_repository;
}

struct ProductService* ProductService__create(struct ProductRepository*);
void ProductService__destroy(struct ProductService*);

void ProductService__add_product(struct ProductService*, ProductId, ProductPrice, ProductAmount, char*, char*, char*);
void ProductService__remove_product(struct ProductService*, ProductId);

struct Product** ProductService__get_products(struct ProductService*);
struct Product** ProductService__get_products_by_brand(struct ProductService*, char*);
struct Product** ProductService__get_products_by_price(struct ProductService*, int);
struct Product** ProductService__get_products_by_amount(struct ProductService*, int);
struct Product* ProductService__get_product_by_id(struct ProductService*, ProductId);

#endif // PRODUCT_SERVICE_H
