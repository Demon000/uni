#include <cstdlib>
#include <cstring>

#include "Colectie.h"

Colectie::Colectie() {
    items = NULL;
    minItem = 0;
    maxItem = 0;
    size = 0;
    total = 0;

    expand(1);
}

void Colectie::expand(int by) {
    void* block;

    if (items) {
        block = realloc(items, sizeof(int) * (size + by));
    } else {
        block = malloc(sizeof(int) * (size + by));
    }

    items = static_cast<int*>(block);
    memset(items + size, 0, sizeof(int) * by);

    size += by;
}

void Colectie::insert(int index, int times) {
    expand(times);

    for (int i = size - 1; i > index - 1; i--) {
        if (i > index + times - 1) {
            items[i] = items[i - times];
        } else {
            items[i] = 0;
        }
    }
}

int Colectie::getOccurances(TElem item) const {
    return items[item - minItem];
}

void Colectie::modifyOccurances(TElem item, int by) {
    items[item - minItem] += by;
    total += by;
}

void Colectie::adauga(TElem item) {
    if (item < minItem) {
        insert(0, minItem - item);
        minItem = item;
    }

    if (item > maxItem) {
        insert(size, item - maxItem);
        maxItem = item;
    }

    modifyOccurances(item, +1);
}

bool Colectie::sterge(TElem item) {
    if (item < minItem || item > maxItem) {
        return false;
    }

    if (getOccurances(item) < 1) {
        return false;
    }

    modifyOccurances(item, -1);
    return true;
}

int Colectie::nrAparitii(TElem item) const {
    if (item < minItem || item > maxItem) {
        return 0;
    }

    return getOccurances(item);
}

bool Colectie::cauta(TElem item) const {
    return nrAparitii(item) != 0;
}

int Colectie::dim() const {
    return total;
}

bool Colectie::vida() const {
    return dim() == 0;
}

Colectie::~Colectie() {
    free(items);
}

IteratorColectie Colectie::iterator() {
    return IteratorColectie(this);
}
