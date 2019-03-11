#include "../utils/Vector.h"
#include "../entities/Product.h"

#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

typedef struct ProductRepository {
    Vector* products;
} ProductRepository;

ProductRepository* ProductRepository__create();
void ProductRepository__destroy(ProductRepository*);

void ProductRepository__add_product(ProductRepository*, Product*);
void ProductRepository__remove_product(ProductRepository*, Product*);

Product* ProductRepository__get_product_by_id(ProductRepository*, ProductId);

ProductsList* ProductRepository__get_products(ProductRepository*);
ProductsList* ProductRepository__get_products_by_brand(ProductRepository*, char*);
ProductsList* ProductRepository__get_products_by_price(ProductRepository*, ProductPrice);
ProductsList* ProductRepository__get_products_by_amount(ProductRepository*, ProductAmount);
void ProductRepository__free_products(ProductsList*);

#endif // PRODUCT_REPOSITORY_H
