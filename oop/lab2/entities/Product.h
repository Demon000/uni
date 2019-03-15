#ifndef PRODUCT_H
#define PRODUCT_H

#define PRODUCT_STRING_MAX_SIZE 32
#define PRODUCT_REPRESENTATION_MAX_SIZE 256

typedef int ProductId;
typedef int ProductPrice;
typedef int ProductAmount;

typedef struct Pruduct {
    ProductId id;
    ProductPrice price;
    ProductAmount amount;

    char type[PRODUCT_STRING_MAX_SIZE];
    char brand[PRODUCT_STRING_MAX_SIZE];
    char model[PRODUCT_STRING_MAX_SIZE];
} Product;

typedef struct ProductsList {
    Product** items;
    int length;
} ProductsList;

/**
 * Create a new product using the provided data.
 *
 * @param id The id of the product.
 * @param price The price of the product.
 * @param amount The amount of the product.
 * @param type The type of the product.
 * @param brand The brand of the product.
 * @param model The model of the product.
 *
 * @return A pointer to the created product.
 */
Product* Product__create(ProductId, ProductPrice, ProductAmount, char*, char*, char*);

/**
 * Set the price of a product.
 *
 * @param product A pointer to the product.
 * @param price The new price of the product.
 */
void Product__set_price(Product*, ProductPrice);

/**
 * Set the amount of a product.
 *
 * @param product A pointer to the product.
 * @param amount The new amount of the product.
 */
void Product__set_amount(Product*, ProductAmount);

/**
 * Destroy a product.
 *
 * @param product A pointer to the product.
 */
void Product__destroy(Product*);

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

#endif //PRODUCT_H
