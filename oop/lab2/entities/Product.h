#ifndef PRODUCT_H
#define PRODUCT_H

#define PRODUCT_STRING_MAX_SIZE 32
#define PRODUCT_REPRESENTATION_MAX_SIZE 256

typedef int ProductId
typedef int ProductPrice
typedef int ProductAmount

struct Pruduct {
    ProductId id;
    ProductPrice price;
    ProductAmount amount;

    char type[PRODUCT_STRING_MAX_SIZE];
    char brand[PRODUCT_STRING_MAX_SIZE];
    char model[PRODUCT_STRING_MAX_SIZE];
};

struct Product* Product__create(ProductId, ProductPrice, ProductAmount, char*, char*, char*);
void Product__destroy(struct Product*);

void Product__set_price(struct Product*, int);
void Product__set_amount(struct Product*, int);

char* Product__get_str(struct Product*);
void Product__free_str(char*);

#endif //PRODUCT_H
