#ifndef SOMMET_H
#define SOMMET_H

#include "global.h"

namespace Graphe
{
	// ---------------------------------------------------------
	// ---------------------  Sommet  --------------------------
	// ---------------------------------------------------------

	template<class T> class Sommet
		// <Sommet> represente un sommet donnée dans un graphe
		// qui contien des informations
	{
	public:
		Sommet();
		explicit Sommet(T sommet);
		Sommet(T sommet, wxPoint p);
		~Sommet();

		// modifier le nom du sommet
		void set(T n_sommet);

		// avoir le nom du sommet
		T get() const;

		// modifier la position du sommet
		void position(wxPoint p);

		// avoir la position du sommet
		wxPoint position() const;

		// dessiner le sommet dans une DC
		void dessiner(wxDC& dc, uint i);

	protected:
		T id;
		wxPoint pos;
	};

	// representation du sommet en sortie
	template<class T> std::ostream& operator<<(std::ostream& , const Sommet<T>&);
	
	// representation du sommet en sortie
	template<class T> std::istream& operator>>(std::istream&, Sommet<T>&);

	// difference entre sommet !!!
	template<class T> bool operator==(const Sommet<T>&, const Sommet<T>&);
	template<class T> bool operator!=(const Sommet<T>&, const Sommet<T>&);
	template<class T> bool operator<(const Sommet<T>&, const Sommet<T>&);

} // namespace Graphe

#endif // SOMMET_GUARD