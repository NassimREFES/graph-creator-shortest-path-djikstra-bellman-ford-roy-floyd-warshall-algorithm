#ifndef DIJKSTRA_GUARD
#define DIJKSTRA_GUARD

#ifndef ACC_GUARD
	#include "acc.h"
	#include "acc.cpp"
#endif

namespace Algorithme
{
	namespace Court_chemin
	{
			// ---------------------------------------------------------
			// ------------ Algorithme Dijkstra ------------------------
			// ---------------------------------------------------------

			template<class TA, class TS> class Dijkstra : public ACC<TA, TS>
			{
			public:
				Dijkstra(Graphe_value<TA, TS> graphe, Sommet<TS> source);

			private:
				// marquage d'un sommet
				std::vector<bool> m_marque;

				// plus petit chemin est pris ( avoir le sommet non marqué avec la plus petit valeur )
				uint min_distance();

				// avoir le poid du lien au sommet pair (u, v)
				TA trouver_poid(uint u, uint v) const;

				// determiner si un des poids dans le graphe est negative
				bool poid_negative() const;

			protected:
				// initialisation des distances
				void init_distance();

				// calcule du plus court chemin entre la source et les autres sommets
				void calcule_distance();
			};
	} // namespace Court_chemin
} // namespace Algorithme

#endif // DIJKSTRA_GUARD