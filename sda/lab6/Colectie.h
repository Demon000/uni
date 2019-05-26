#ifndef COLECTIE_H
#define COLECTIE_H

#define INITIAL_SIZE 7
#define SIZE_FACTOR 131
#define MISSING_VALUE 2<<28
#define MISSING_POSITION 2<<28

typedef int TElem;

class IteratorColectie;

class Colectie {
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

private:
    TElem* elements;
    int* nextElements;
    int total;
    int capacity;
    int firstFree;

    void print();
    void expand(int);
    int findFirstFree();
    int hash(TElem) const;
    void innerAdd(TElem);
    void add(TElem);
    bool remove(TElem);
    int occurances(TElem) const;
    bool find(TElem) const;
    int size() const;
};

class IteratorColectie {
public:
    void prim();
    void urmator();
    bool valid() const;
    TElem element() const;

private:
    IteratorColectie(const Colectie*);

    const Colectie* collection;
    int position;

    friend class Colectie;
};

#endif // COLECTIE_H
