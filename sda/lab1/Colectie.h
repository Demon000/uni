#ifndef COLECTIE_H
#define COLECTIE_H

typedef int TElem;

class IteratorColectie;

class Colectie {
private:
    TElem minItem;
    TElem maxItem;
    int* items;
    int size;
    int total;

    void expand(int);
    void insert(int, int);
    void modifyOccurances(TElem, int);
    int getOccurances(TElem) const;

    friend class IteratorColectie;

public:
    Colectie();

    void adauga(TElem);
    bool sterge(TElem);
    bool cauta(TElem) const;
    int nrAparitii(TElem) const;
    int dim() const;
    bool vida() const;
    void goleste();
    IteratorColectie iterator();
    ~Colectie();
};

class IteratorColectie {
private:
    IteratorColectie(const Colectie*);
    void moveToFirstOccuring(int);

    const Colectie* collection;
    int occurances;
    TElem current;

    friend class Colectie;

public:
    void prim();
    void urmator();
    bool valid() const;
    TElem element() const;
};

#endif // COLECTIE_H
