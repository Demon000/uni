#include <stdlib.h>

#include "ProductsList.h"

ProductsList* ProductsList__create(int size) {
    ProductsList* list = malloc(sizeof(ProductsList));
    list->items = malloc(sizeof(Product*) * size);
    list->length = 0;
    return list;
}

void ProductsList__add(ProductsList* list, Product* product) {
    list->items[list->length++] = product;
}

int ProductsList__get_length(ProductsList* list) {
    return list->length;
}

Product* ProductsList__get(ProductsList* list, int i) {
    if (i >= list->length) {
        return NULL;
    }

    return list->items[i];
}

void ProductsList__swap(ProductsList* list, int first, int second) {
    if (first < 0 || first >= list->length ||
            second < 0 || second >= list->length) {
        return;
    }

    Product* aux = list->items[first];
    list->items[first] = list->items[second];
    list->items[second] = aux;
}

void ProductsList__destroy(ProductsList* list) {
    free(list->items);
    free(list);
}
