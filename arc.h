#ifndef ARC_GUARD
#define ARC_GUARD

#ifndef ARETE_GUARD
	#include "arete.h"
	#include "arete.cpp"
#endif

namespace Graphe
{
	// ---------------------------------------------------------
	// ---------------------  Arc  -----------------------------
	// ---------------------------------------------------------

	template<class T, class U> struct Arc : Arete < T, U >
		// Arc represente une Arete avec une orientation
		// T  : type de l'arete
		// U  : type des deux sommets
	{
		Arc(T poid = T(), Sommet<U> s_init = Sommet<U>(), Sommet<U> s_fin = Sommet<U>());

		// avoir le sommet initial de l'arc
		Sommet<U>  sommet_initial() const;

		// avoir le sommet final de l'arc
		Sommet<U> sommet_final()   const;

		// dessin de l'arc
		void dessiner(wxDC&, bool, int);
	};

} // namespace Graphe

#endif // ARC_GUARD