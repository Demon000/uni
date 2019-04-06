#include "Colectie.h"

IteratorColectie::IteratorColectie(const Colectie* c) : collection{c} {
    moveToFirstOccuring(collection->minItem);
}

void IteratorColectie::prim() {
    moveToFirstOccuring(collection->minItem);
}

void IteratorColectie::moveToFirstOccuring(int from) {
    current = from;
    occurances = 0;

    for (int i = from; i <= collection->maxItem; i++) {
        if (collection->getOccurances(i)) {
            current = i;
            break;
        }
    }
}

void IteratorColectie::urmator() {
    occurances++;

    if (occurances == collection->getOccurances(current)) {
        moveToFirstOccuring(current + 1);
    }
}

bool IteratorColectie::valid() const {
    if (current > collection->maxItem) {
        return false;
    }

    if (current == collection->maxItem &&
            occurances == collection->getOccurances(current)) {
        return false;
    }

    return true;
}

TElem IteratorColectie::element() const {
    return current;
}
