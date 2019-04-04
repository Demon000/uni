#include "Colectie"

class IteratorColectie {
	private:
		IteratorColectie(const Colectie& c);
		const Colectie& c;
	public:
		void prim();
		void urmator();
		bool valid() const;
		TElem element() const;
};
