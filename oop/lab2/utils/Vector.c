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
    if (index < 0 || index >= v->length) {
        return;
    }

    v->items[index] = item;
}

void* Vector__get(Vector* v, int index) {
    if (index < 0 || index >= v->length) {
        return NULL;
    }

    return v->items[index];
}

void Vector__delete(Vector* v, int index) {
    if (index < 0 || index >= v->length) {
        return;
    }

    v->items[index] = NULL;

    for (int i = index; i < v->length - 1; i++) {
        v->items[i] = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->length--;

    if (v->length > 0 && v->length == v->size / 4) {
        Vector__resize(v, v->size / 2);
    }
}

void Vector__destroy(Vector* v) {
    free(v->items);
    free(v);
}
