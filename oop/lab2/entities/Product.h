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

Product* Product__create(ProductId, ProductPrice, ProductAmount, char*, char*, char*);
void Product__destroy(Product*);

void Product__set_price(Product*, ProductPrice);
void Product__set_amount(Product*, ProductAmount);

ProductsList* ProductsList__create(int);
void ProductsList__destroy(ProductsList*);

void ProductsList__add(ProductsList*, Product*);
int ProductsList__get_length(ProductsList*);
Product* ProductsList__get(ProductsList*, int);
void ProductsList__swap(ProductsList*, int, int);

#endif //PRODUCT_H
