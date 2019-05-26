#include <cstdlib>
#include <iostream>

#include "Colectie.h"

using std::cout;

Colectie::Colectie() {
    elements = NULL;
    nextElements = NULL;
    total = 0;
    capacity = 0;
    firstFree = 0;

    expand(INITIAL_SIZE);
}

void Colectie::expand(int by) {
    TElem* oldElements = elements;

    TElem* newElements = static_cast<TElem*>(malloc(sizeof(TElem) * (capacity + by)));
    int* newNextElements = static_cast<int*>(malloc(sizeof(int) * (capacity + by)));

    elements = newElements;
    nextElements = newNextElements;

    for (int i = 0; i < capacity; i++) {
        TElem element = oldElements[i];
        innerAdd(element);
    }

    for (int i = capacity; i < capacity + by; i++) {
        elements[i] = MISSING_VALUE;
        nextElements[i] = MISSING_POSITION;
    }

    capacity += by;
}

int Colectie::findFirstFree() {
    int position = 0;
    while (elements[position] != MISSING_VALUE) {
        position++;
    }

    return position;
}

int Colectie::hash(TElem element) const {
    return abs(element % capacity);
}

void Colectie::print() {
    for (int i = 0; i < capacity; i++) {
        cout << i << "\t";
    }
    cout << "\n";

    for (int i = 0; i < capacity; i++) {
        cout << elements[i] << "\t";
    }
    cout << "\n";

    for (int i = 0; i < capacity; i++) {
        cout << nextElements[i] << "\t";
    }
    cout << "\n";
    cout << "\n";
}

void Colectie::innerAdd(TElem element) {
    int key = hash(element);
    if (elements[key] == MISSING_VALUE) {
        elements[key] = element;
        return;
    }

    int position = key;
    while (nextElements[position] != MISSING_POSITION) {
        position = nextElements[position];
    }

    nextElements[position] = firstFree;
    elements[firstFree] = element;

    firstFree = findFirstFree();
}

void Colectie::add(TElem element) {
    if (total == capacity) {
        expand(SIZE_FACTOR);
    }

    innerAdd(element);
    total += 1;
    print();
}

bool Colectie::remove(TElem element) {
    int position = hash(element);
    while (true) {
        if (elements[position] == element) {
            break;
        }

        if (elements[position] == MISSING_VALUE) {
            return false;
        }

        position = nextElements[position];
    }

    int nextPosition = nextElements[position];
    while (true) {
        if (nextPosition == MISSING_POSITION) {
            break;
        }

        elements[position] = elements[nextPosition];

        position = nextElements[position];
        nextPosition = nextElements[nextPosition];
    }

    elements[position] = MISSING_VALUE;
    nextElements[position] = MISSING_POSITION;

    firstFree = position;

    print();
    total -= 1;

    return true;
}

int Colectie::occurances(TElem element) const {
    int key = hash(element);
    int n = 0;

    int position = key;
    while (true) {
        if (elements[position] == element) {
            n++;
        }

        if (nextElements[position] == MISSING_POSITION) {
            break;
        }

        position = nextElements[position];
    }

    return n;
}

bool Colectie::find(TElem element) const {
    for (int i = 0; i < capacity; i++) {
        if (elements[i] == element) {
            return true;
        }
    }

    return false;
}

int Colectie::size() const {
    return total;
}

void Colectie::adauga(TElem element) {
    add(element);
}

bool Colectie::sterge(TElem element) {
    return remove(element);
}

int Colectie::nrAparitii(TElem element) const {
    return occurances(element);
}

bool Colectie::cauta(TElem element) const {
    return find(element);
}

int Colectie::dim() const {
    return size();
}

bool Colectie::vida() const {
    return size() == 0;
}

Colectie::~Colectie() {
    free(elements);
    free(nextElements);
}

IteratorColectie Colectie::iterator() {
    return IteratorColectie(this);
}
