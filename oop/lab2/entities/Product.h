#ifndef PRODUCT_H
#define PRODUCT_H

#define PRODUCT_STRING_MAX_SIZE 32

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

typedef enum ProductError {
    PRODUCT_NO_ERROR,
    PRODUCT_NOT_FOUND,
} ProductError;

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
 * Get the id of a product.
 *
 * @param product A pointer to the product.
 *
 * @return The id of the product.
 */
ProductId Product__get_id(Product*);

/**
 * Get the price of a product.
 *
 * @param product A pointer to the product.
 *
 * @return The price of the product.
 */
ProductPrice Product__get_price(Product*);

/**
 * Get the amount of a product.
 *
 * @param product A pointer to the product.
 *
 * @return The amount of the product.
 */
ProductAmount Product__get_amount(Product*);

/**
 * Get the type of a product.
 *
 * @param product A pointer to the product.
 *
 * @return The type of the product.
 */
char* Product__get_type(Product*);

/**
 * Get the brand of a product.
 *
 * @param product A pointer to the product.
 *
 * @return The brand of the product.
 */
char* Product__get_brand(Product*);

/**
 * Get the model of a product.
 *
 * @param product A pointer to the product.
 *
 * @return The model of the product.
 */
char* Product__get_model(Product*);

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

#endif //PRODUCT_H
