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
 * @param id The id of the product to be created.
 * @param price The price of the product to be created.
 * @param amount The amount of the product to be created.
 * @param type The type of the product to be created.
 * @param brand The brand of the product to be created.
 * @param model The model of the product to be created.
 *
 * @return A pointer to the newly created product.
 */
Product* Product__create(ProductId, ProductPrice, ProductAmount, char*, char*, char*);

/**
 * Destroy a product.
 *
 * @param product A pointer to a product.
 */
void Product__destroy(Product*);

/**
 * Set the price of a product.
 *
 * @param product A pointer to the product to set the price for.
 * @param price The new price of the product.
 */
void Product__set_price(Product*, ProductPrice);

/**
 * Set the amount of a product.
 *
 * @param product A pointer to the product to set the price for.
 * @param amount The new amount of the product.
 */
void Product__set_amount(Product*, ProductAmount);

/**
 * Create a list of products with a static length.
 *
 * @param size The maximum size of the list.
 *
 * @return A pointer to the newly created products list.
 */
ProductsList* ProductsList__create(int);

/**
 * Destroy a list of products.
 *
 * @param list A pointer to a list of products.
 */
void ProductsList__destroy(ProductsList*);

/**
 * Add a product to a list of products.
 *
 * @param list A pointer to a list of products.
 * @param product A pointer to a product.
 */
void ProductsList__add(ProductsList*, Product*);

/**
 * Get the length of a list of products.
 *
 * @param list A pointer to a list of products.
 *
 * @return The length of the list of products.
 */
int ProductsList__get_length(ProductsList*);

/**
 * Get a product from a list of products.
 *
 * @param list A pointer to a list of products.
 * @param index The index at which the desired product is situated.
 *
 * @return A pointer to the desired product.
 */
Product* ProductsList__get(ProductsList*, int);

/**
 * Swap two products from a list of products.
 *
 * @param list A pointer to a list of products.
 * @param first The index of the first product.
 * @param second The index of the second product.
 */
void ProductsList__swap(ProductsList*, int, int);

#endif //PRODUCT_H
