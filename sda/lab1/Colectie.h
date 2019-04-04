#ifndef COLECTIE_H
#define COLECTIE_H

typedef int TElem;

class IteratorColectie;

class Colectie {
	private:

	public:
		Colectie();

		void adauga(TElem e);
		bool sterge(TElem e);
		bool cauta(TElem elem) const;
		int nrAparitii(TElem elem) const;
		int dim() const;
		bool vida() const;
		IteratorColectie iterator() const;
		~Colectie();
};

class IteratorColectie {
	private:
		IteratorColectie(const Colectie& c);
		const Colectie& c;

		friend class Colectie;
	public:
		void prim();
		void urmator();
		bool valid() const;
		TElem element() const;
};

#endif // COLECTIE_H
