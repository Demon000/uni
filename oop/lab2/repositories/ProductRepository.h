#include "../utils/Vector.h"
#include "../entities/Product.h"

#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

typedef struct ProductRepository {
    struct Vector* products;
} ProductRepository;

ProductRepository* ProductRepository__create();
void ProductRepository__destroy(ProductRepository*);

void ProductRepository__add_product(ProductRepository*, Product*);
void ProductRepository__remove_product(ProductRepository*, Product*);

Product** ProductRepository__get_products(ProductRepository*);
Product** ProductRepository__get_products_by_brand(ProductRepository*, char*);
Product** ProductRepository__get_products_by_price(ProductRepository*, int);
Product** ProductRepository__get_products_by_amount(ProductRepository*, int);
Product* ProductRepository__get_product_by_id(ProductRepository*, ProductId);

#endif // PRODUCT_REPOSITORY_H
