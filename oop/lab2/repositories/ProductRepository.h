#include "../utils/Vector.h"
#include "../entities/Product.h"

#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_H

typedef struct ProductRepository {
    Vector* products;
} ProductRepository;

/**
 * Create a product repository.
 *
 * @return A pointer to the newly created product repository.
 */
ProductRepository* ProductRepository__create();

/**
 * Add a product to a product repository.
 *
 * @param repository A pointer to the product repository.
 * @param product A pointer to the product to be added.
 */
void ProductRepository__add_product(ProductRepository*, Product*);

/**
 * Get a product from a product repository by the product id.
 *
 * @param repository A pointer to the product repository.
 * @param id The id to look for.
 *
 * @return A pointer to the product if found, NULL otherwise.
 */
Product* ProductRepository__get_product_by_id(ProductRepository*, ProductId);

/**
 * Get all the products from a product repository.
 *
 * @param repository A pointer to the product repository.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductRepository__get_products(ProductRepository*);

/**
 * Get all the products matching the provided brand from a product repository.
 *
 * @param repository A pointer to the product repository.
 * @param brand The brand to look for.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductRepository__get_products_by_brand(ProductRepository*, char*);

/**
 * Get all the products matching the provided price from a product repository.
 *
 * @param repository A pointer to the product repository.
 * @param price The price to look for.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductRepository__get_products_by_price(ProductRepository*, ProductPrice);

/**
 * Get all the products matching the provided amount from a product repository.
 *
 * @param repository A pointer to the product repository.
 * @param amount The amount to look for.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductRepository__get_products_by_amount(ProductRepository*, ProductAmount);

/**
 * Update a product from a product repository.
 *
 * @param repository A pointer to the product repository.
 * @param product A pointer to the product to be updated.
 */
void ProductRepository__update_product(ProductRepository*, Product*, ProductPrice, ProductAmount);

/**
 * Remove a product from a product repository.
 *
 * @param repository A pointer to the product repository.
 * @param product A pointer to the product to be removed.
 */
void ProductRepository__remove_product(ProductRepository*, Product*);

/**
 * Destroy a product repository.
 *
 * @param repository A pointer to the product repository.
 */
void ProductRepository__destroy(ProductRepository*);

#endif // PRODUCT_REPOSITORY_H
