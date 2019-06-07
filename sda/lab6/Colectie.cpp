#include <cstdlib>
#include <iostream>

#include "Colectie.h"

using std::cout;

Colectie::Colectie() {
    elements = NULL;
    nextElements = NULL;
    used = 0;
    total = 0;
    capacity = 0;
    firstFree = 0;

    expand();
}

void Colectie::expand() {
    int newCapacity;

    // force allocate on initial expand
    if (used < capacity && capacity != 0) {
        return;
    }

    // assign initial value
    if (capacity == 0) {
        newCapacity = SIZE_FACTOR;
    } else {
        newCapacity = capacity * SIZE_FACTOR;
    }

    // keep a pointer to the old vectors
    TElem* oldElements = elements;
    int* oldNextElements = nextElements;
    bool* oldIsDeleted = isDeleted;
    int oldCapacity = capacity;

    // alocate new vectors
    TElem* newElements = static_cast<TElem*>(malloc(sizeof(TElem) * newCapacity));
    int* newNextElements = static_cast<int*>(malloc(sizeof(int) * newCapacity));
    bool* newIsDeleted = static_cast<bool*>(malloc(sizeof(bool) * newCapacity));

    // initialize the whole new vectors
    for (int i = 0; i < newCapacity; i++) {
        newElements[i] = MISSING_VALUE;
        newNextElements[i] = MISSING_POSITION;
        newIsDeleted[i] = false;
    }

    // assign the new vectors to use the innerAdd function we already have
    elements = newElements;
    nextElements = newNextElements;
    isDeleted = newIsDeleted;
    capacity = newCapacity;
    used = 0;

    // if capacity is 0, this is the initial expand
    // so don't do anything to the contents of the old vectors
    if (oldCapacity != 0) {
        // re-add each element not missing in the old vector
        for (int i = 0; i < oldCapacity; i++) {
            if (!oldIsDeleted[i]) {
                innerAdd(oldElements[i]);
            }
        }

        free(oldElements);
        free(oldNextElements);
        free(oldIsDeleted);
    }
}

void Colectie::findFirstFree() {
    int position = 0;
    while (true) {
        if (position == capacity) {
            // we filled the list, there are no left positions
            // set the next free position to the current capacity
            // the list will be exanded on the next add
            break;
        }

        if (elements[position] == MISSING_VALUE) {
            // we found the first position without a value
            break;
        }

        // advance a positiion
        position++;
    }

    firstFree = position;
}

int Colectie::hash(TElem element) const {
    return abs(element % capacity);
}

void Colectie::innerAdd(TElem element) {
    // we want to put our element at the position of our hash
    int targetPosition = hash(element);

    if (elements[targetPosition] != MISSING_VALUE) {
        // the position of our hash is not empty
        // find the last position of elements sitting at our hash
        // since we need to make it point to our target position
        // which is the first free position
        int previousPosition = targetPosition;

        while (true) {
            // we found the last element in the chain
            if (nextElements[previousPosition] == MISSING_POSITION) {
                break;
            }

            // advance a position
            previousPosition = nextElements[previousPosition];
        }

        // make sure the last element in the chain points at
        // the target position
        targetPosition = firstFree;
        nextElements[previousPosition] = firstFree;
    }

    // put element on the target position
    elements[targetPosition] = element;

    // increase the used count
    used++;

    if (targetPosition == firstFree) {
        // find the first free position if we occupied it
        findFirstFree();
    }
}

void Colectie::add(TElem element) {
    expand();

    innerAdd(element);
    total += 1;
}

bool Colectie::remove(TElem element) {
    int targetPosition = hash(element);

    while (true) {
        if (elements[targetPosition] == element &&
                isDeleted[targetPosition] != true) {
            // we found our element
            // mark it as deleted
            isDeleted[targetPosition] = true;
            break;
        }

        if (nextElements[targetPosition] == MISSING_POSITION) {
            // we found the last element in the chain
            return false;
        }

        // advance a position
        targetPosition = nextElements[targetPosition];
    }

    total--;
    return true;
}

int Colectie::occurances(TElem element) const {
    int targetPosition = hash(element);
    int n = 0;

    while (true) {
        // check if this is our element
        // but ignore our element if it has been deleted
        if (elements[targetPosition] == element &&
                isDeleted[targetPosition] != true) {
            n++;
        }

        if (nextElements[targetPosition] == MISSING_POSITION) {
            // we found the last element in the chain
            break;
        }

        // advance a position
        targetPosition = nextElements[targetPosition];
    }

    return n;
}

bool Colectie::exists(TElem element) const {
    return occurances(element);
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

int Colectie::stergeMultiple(int nr, TElem element) {
    int sterse = 0;
    bool sters;

    while (nr) {
        sters = sterge(element);
        if (sters) {
            sterse++;
        }

        nr--;
    }

    return sterse;
}

int Colectie::nrAparitii(TElem element) const {
    return occurances(element);
}

bool Colectie::cauta(TElem element) const {
    return exists(element);
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
    free(isDeleted);
}

IteratorColectie Colectie::iterator() {
    return IteratorColectie(this);
}
