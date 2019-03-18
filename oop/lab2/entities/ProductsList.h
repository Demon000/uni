#include "Product.h"

#ifndef PRODUCTS_LIST_H
#define PRODUCTS_LIST_H

typedef struct ProductsList {
    Product** items;
    int size;
    int length;
} ProductsList;

typedef int (*ProductsListSortFn)(Product*, Product*);

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
 * Sort a list of products.
 *
 * @param list A pointer to the list of products.
 * @param sort_fn A pointer to a function which decides which product comes first.
 */
void ProductsList__sort(ProductsList*, ProductsListSortFn);

/**
 * Destroy a list of products.
 *
 * @param list A pointer to the list of products.
 */
void ProductsList__destroy(ProductsList*);

#endif // PRODUCTS_LIST_H
