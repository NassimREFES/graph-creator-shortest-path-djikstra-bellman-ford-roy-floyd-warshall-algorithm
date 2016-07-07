#ifndef ARETE_GUARD
#define ARETE_GUARD

#ifndef SOMMET_GUARD
	#include "sommet.h"
	#include "sommet.cpp"
#endif

namespace Graphe
{
	// ---------------------------------------------------------
	// -------------------  Arete  -----------------------------
	// ---------------------------------------------------------

	template<class T, class U> class Arete
		// Arete represente un lien entre une pair de sommets
		// T  : type de l'arete
		// U  : type des deux sommets
	{
	public:
		// construction d'une arete
		Arete(T poid, Sommet<U> s1, Sommet<U> s2);
		Arete(const Arete<T, U>&);
		Arete& operator=(const Arete<T, U>&);

		// detruire l'arete
		~Arete();

		// modifier le poid de l'arete
		void set_poid(T n_poid);

		// avoir le poid de l'arete
		T poid() const;

		// avoir la pair de sommet de l'arete
		std::pair< Sommet<U>, Sommet<U> > sommets() const;

		// modifier la pair de sommet de l'arete
		void sommets(std::pair< Sommet<U>, Sommet<U> > s);

		/* 
		   dessin de l'arete
		   retourne l'angle utilisé pour le reglage de l'arete
		*/
		double dessiner(wxDC& dc, bool afficher_poid, int count);
	protected:
		std::pair< Sommet<U>, Sommet<U> > m_sommets;
		T m_poid;
	};

	template<class T, class U> std::istream& operator>>(std::istream&, Arete<T, U>&);

	// comparer le poid de deux arete
	template<class T, class U, class V>
	inline bool operator==(const Arete<T, U>&, const Arete<T, V>&);

	template<class T, class U, class V>
	inline bool operator<(const Arete<T, U>&, const Arete<T, V>&);

} // namespace Graphe

#endif // ARETE_GUARD