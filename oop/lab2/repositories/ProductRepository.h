#include "../utils/Vector.h"
#include "../entities/Product.h"

#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

struct ProductRepository {
    struct Vector* products;
};

struct ProductRepository* ProductRepository__create();
void ProductRepository__destroy(struct ProductRepository*);

void ProductRepository__add_product(struct Product*);
void ProductRepository__remove_product(struct Product*);

struct Product** ProductRepository__get_products(struct ProductRepository*);
struct Product** ProductRepository__get_products_by_brand(struct ProductRepository*, char*);
struct Product** ProductRepository__get_products_by_price(struct ProductRepository*, int);
struct Product** ProductRepository__get_products_by_amount(struct ProductRepository*, int);
struct Product* ProductRepository__get_product_by_id(struct ProductRepository*, ProductId);

#endif // PRODUCT_REPOSITORY_H
