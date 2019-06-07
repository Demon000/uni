#include "Colectie.h"

IteratorColectie::IteratorColectie(const Colectie* c) : collection{c} {
    prim();
}

void IteratorColectie::prim() {
    position = -1;
    urmator();
}

void IteratorColectie::urmator() {
    position++;
    for (int i = position; i < collection->capacity; i++) {
        if (collection->elements[position] != MISSING_VALUE) {
            break;
        }
    }
}

bool IteratorColectie::valid() const {
    return position != collection->total;
}

TElem IteratorColectie::element() const {
    return collection->elements[position];
}
