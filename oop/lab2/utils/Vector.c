#include <stdlib.h>

#include "Vector.h"

Vector* Vector__create() {
    Vector* v = malloc(sizeof(Vector));

    v->size = VECTOR_INIT_SIZE;
    v->length = 0;
    v->items = malloc(sizeof(void *) * v->size);

    return v;
}

int Vector__get_length(Vector* v) {
    return v->length;
}

void Vector__resize(Vector* v, int size) {
    void **items = realloc(v->items, sizeof(void *) * size);

    if (items) {
        v->items = items;
        v->size = size;
    }
}

void Vector__add(Vector* v, void *item) {
    if (v->size == v->length) {
        Vector__resize(v, v->size * 2);
    }

    v->items[v->length++] = item;
}

void Vector__set(Vector* v, int index, void *item) {
    v->items[index] = item;
}

void* Vector__get(Vector* v, int index) {
    return v->items[index];
}

void Vector__delete(Vector* v, int index) {
    v->items[index] = NULL;

    for (int i = index; i < v->length - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->length--;
}

void Vector__sort(Vector* v, VectorSortFn sort_fn) {
    for (int i = 0; i < v->length; i++) {
        for (int j = i + 1; j < v->length; j++) {
            void* first = v->items[i];
            void* second = v->items[j];
            int value = sort_fn(first, second);

            if (value < 0) {
                void* aux = v->items[i];
                v->items[i] = v->items[j];
                v->items[j] = aux;
            }
        }
    }
}

void Vector__destroy(Vector* v) {
    free(v->items);
    free(v);
}
