#include "Product.h"

#ifndef PRODUCTS_LIST_H
#define PRODUCTS_LIST_H

typedef struct ProductsList {
    Product** items;
    int size;
    int length;
} ProductsList;

/**
 * Create a list of products with a static length.
 *
 * @param size The maximum size of the list.
 *
 * @return A pointer to the created products list.
 */
ProductsList* ProductsList__create(int);

/**
 * Add a product to a list of products.
 *
 * @param list A pointer to the list of products.
 * @param product A pointer to the product.
 */
void ProductsList__add(ProductsList*, Product*);

/**
 * Get the length of a list of products.
 *
 * @param list A pointer to the list of products.
 *
 * @return The length of the list of products.
 */
int ProductsList__get_length(ProductsList*);

/**
 * Get a product from a list of products.
 *
 * @param list A pointer to the list of products.
 * @param index The index at which the desired product can be found.
 *
 * @return A pointer to the desired product if found, NULL otherwise.
 */
Product* ProductsList__get(ProductsList*, int);

/**
 * Swap two products from a list of products.
 *
 * @param list A pointer to the list of products.
 * @param first The index of the first product.
 * @param second The index of the second product.
 */
void ProductsList__swap(ProductsList*, int, int);

/**
 * Destroy a list of products.
 *
 * @param list A pointer to the list of products.
 */
void ProductsList__destroy(ProductsList*);

#endif // PRODUCTS_LIST_H
