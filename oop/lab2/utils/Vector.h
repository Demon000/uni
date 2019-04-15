#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_SIZE 4

typedef int (*VectorSortFn)(void*, void*);

typedef struct Vector {
    void **items;
    int size;
    int length;
} Vector;

/**
 * Create a vector.
 *
 * @return A pointer to the newly created vector.
 */
Vector* Vector__create();

/**
 * Get the length of a vector.
 *
 * @param vector A pointer to the vector.
 *
 * @return The length of the vector.
 */
int Vector__get_length(Vector*);

/**
 * Add an item to the vector.
 *
 * @param vector A pointer to the vector.
 * @param item A pointer to the item.
 */
void Vector__add(Vector*, void *);

/**
 * Set an index of the vector to an item.
 *
 * @param vector A pointer to the vector.
 * @param index An index number.
 * @param A pointer to the item.
 */
void Vector__set(Vector*, int, void *);

/**
 * Get the item found at an index.
 *
 * @param vector A pointer to the vector.
 * @param index An index number.
 *
 * @return A pointer to an item.
 */
void* Vector__get(Vector*, int);

/**
 * Delete the item found at an index.
 *
 * @param vector A pointer to the vector.
 * @param index An index number.
 */
void Vector__delete(Vector*, int);

/**
 * Sort the items of the vector.
 *
 * @param vector A pointer to the vector.
 * @param sort_fn A comparator function.
 */
void Vector__sort(Vector*, VectorSortFn);

/**
 * Destroy a vector.
 *
 * @param vector A pointer to the vector.
 */
void Vector__destroy(Vector*);

#endif
