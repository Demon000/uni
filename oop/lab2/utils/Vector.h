#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_SIZE 4

struct Vector {
    void **items;
    int size;
    int length;
};

void Vector__create();
void Vector__destroy(struct Vector*);

int Vector__get_length(struct Vector*);
void Vector__add(struct Vector*, void *);
void Vector__set(struct Vector*, int, void *);
void* Vector__get(struct Vector*, int);
void Vector__delete(struct Vector*, int);

#endif
