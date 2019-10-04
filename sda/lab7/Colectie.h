#ifndef COLECTIE_H
#define COLECTIE_H

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
    void print() const;

private:
    void expand();
    void add(TElem);
    bool exists(TElem) const;
    bool remove(TElem);
    int occurances(TElem) const;
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
