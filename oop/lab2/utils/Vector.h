#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_SIZE 4

typedef struct Vector {
    void **items;
    int size;
    int length;
} Vector;

Vector* Vector__create();
void Vector__destroy(Vector*);

int Vector__get_length(Vector*);
void Vector__add(Vector*, void *);
void Vector__set(Vector*, int, void *);
void* Vector__get(Vector*, int);
void Vector__delete(Vector*, int);

#endif
