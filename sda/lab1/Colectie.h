#include "IteratorColectie.h"

typedef int TElem;

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
