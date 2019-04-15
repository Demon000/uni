#include "../utils/Vector.h"
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

/**
 * Create a product service.
 *
 * @param repository A pointer to the repository to use for product storage.
 *
 * @return A pointer to the newly created product service.
 */
ProductService* ProductService__create(ProductRepository*);

/**
 * Create a product and add it to the repository if the id doesn't already
 * exist, or update the amount if it does.
 *
 * @param id The id of the product.
 * @param price The price of the product.
 * @param amount The amount of the product.
 * @param type The type of the product.
 * @param brand The brand of the product.
 * @param model The model of the product.
 *
 * @return A pointer to the newly created or updated product.
 */
Product* ProductService__add_product(ProductService*, ProductId, ProductPrice, ProductAmount, char*, char*, char*);

/**
 * Get all the products sorted by the provided type and order.
 *
 * @param service A pointer to the product service.
 * @param type The type of sort to apply.
 * @param order The order of the sort.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductService__get_sorted_products(ProductService*, ProductSortType, ProductSortOrder);

/**
 * Get all the products from a product service.
 *
 * @param service A pointer to the product service.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductService__get_products(ProductService*);

/**
 * Get all the products matching the provided brand from a product service.
 *
 * @param service A pointer to the product service.
 * @param brand The brand to look for.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductService__get_products_by_brand(ProductService*, char*);

/**
 * Get all the products matching the provided price from a product service.
 *
 * @param service A pointer to the product service.
 * @param price The price to look for.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductService__get_products_by_price(ProductService*, ProductPrice);

/**
 * Get all the products matching the provided amount from a product service.
 *
 * @param service A pointer to the product service.
 * @param amount The amount to look for.
 *
 * @return A pointer to the vector of products.
 */
Vector* ProductService__get_products_by_amount(ProductService*, ProductAmount);

/**
 * Find a product by id and update it.
 *
 * @param id The id of the product.
 * @param price The new price of the product.
 * @param amount The new amount of the product.
 *
 * @return A pointer to the updated product.
 */
Product* ProductService__update_product(ProductService*, ProductId, ProductPrice, ProductAmount);

/**
 * Find a product by id and remove it from the repository.
 *
 * @param id The id of the product.
 *
 * @return PRODUCT_NO_ERROR if the product has been deleted,
 *      PRODUCT_NOT_FOUND couldn't be found.
 */
ProductError ProductService__remove_product(ProductService*, ProductId);

/**
 * Destroy a product service.
 *
 * @param A pointer to the product service.
 */
void ProductService__destroy(ProductService*);

#endif // PRODUCT_SERVICE_H
