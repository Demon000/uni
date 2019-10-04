#include <cstdlib>
#include <iostream>

#include "Colectie.h"

using std::cout;

Colectie::Colectie() {
}

void Colectie::expand() {
}

void Colectie::add(TElem element) {
}

bool Colectie::remove(TElem element) {
}

int Colectie::occurances(TElem element) const {
}

bool Colectie::exists(TElem element) const {
    return occurances(element);
}

int Colectie::size() const {
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
    return exists(element);
}

int Colectie::dim() const {
    return size();
}

bool Colectie::vida() const {
    return size() == 0;
}

Colectie::~Colectie() {
}

IteratorColectie Colectie::iterator() {
    return IteratorColectie(this);
}
