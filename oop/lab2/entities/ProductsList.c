#include <stdlib.h>

#include "ProductsList.h"

ProductsList* ProductsList__create(int size) {
    ProductsList* list = malloc(sizeof(ProductsList));
    list->size = size;
    list->length = 0;
    list->items = malloc(sizeof(Product*) * size);

    return list;
}

void ProductsList__add(ProductsList* list, Product* product) {
    if (list->length == list->size) {
        return;
    }

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

void ProductsList__sort(ProductsList* list, ProductsListSortFn sort_fn) {
    for (int i = 0; i < list->length; i++) {
        for (int j = i + 1; j < list->length; j++) {
            Product* first = list->items[i];
            Product* second = list->items[j];
            int value = sort_fn(first, second);

            if (value < 0) {
                Product* aux = list->items[i];
                list->items[i] = list->items[j];
                list->items[j] = aux;
            }
        }
    }
}

void ProductsList__destroy(ProductsList* list) {
    free(list->items);
    free(list);
}
