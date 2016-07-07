#ifndef ROY_FLOYD_WARSHALL_GUARD
#define ROY_FLOYD_WARSHALL_GUARD

#include "global.h"

#ifndef ACC_GUARD
#include "acc.h"
#include "acc.cpp"
#endif 

namespace Algorithme
{
	namespace Court_chemin
	{
		// ---------------------------------------------------------
		// ------------ Algorithme Roy-Floyd-Warshall --------------
		// ---------------------------------------------------------

		template<class TA, class TS> class Roy_floyd_warshall : public ACC<TA, TS>
		{
		public:
			Roy_floyd_warshall(Graphe_value<TA, TS> graphe, Sommet<TS> source);

			// la valeur de la distance du plus cours chemin pris
			TA distance_dl_source_vers(Sommet<TS> d) const;

			// le chemin de la source vers le destinataire
			std::vector< Sommet<TS> > parcour_dl_source_vers(Sommet<TS> destinataire) const;

			// Le Tracé de l'algorithme
			const std::vector< std::vector< std::vector<TA> > >& trace_matrice() const;

			// Le Tracé du resultat final de l'algorithme
			std::vector < std::vector<TA> > trace() const;

		protected:
			void init_distance();
			void calcule_distance();

		private:
			std::vector< std::vector<TA> > m_graphe_matrice;
			std::vector< std::vector<TA> > m_dist_matrice;
			std::vector< std::vector<TA> > m_parent_matrice;
			std::vector< std::vector< std::vector<TA> > > m_trace_matrice;

		private:
			void graphe_to_matrice();
		};

	} // namespace Court_chemin
} // namespace Algorithme


#endif // ROY_FLOYD_WARSHALL_GUARD