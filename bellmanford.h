#ifndef BELLMANFORD_GUARD
#define BELLMANFORD_GUARD

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
			// ------------ Algorithme BellmanFord ---------------------
			// ---------------------------------------------------------

			template<class TA, class TS> class BellmanFord : public ACC<TA, TS>
			{
			public:
				BellmanFord(Graphe_value<TA, TS> graphe, Sommet<TS> source);

			protected:
				// initialiser distance de la source vers tout les autres sommets a infini ( max du type numeric utilisé )
				void init_distance();

				// calcule du plus court chemin entre la source et les autres sommets( |nombre_sommet| - 1 )
				void calcule_distance();

				// determiner si le graphe contien un cycle negative (circuit absorbant)
				bool cycle_negative();
			};

	} // namespace Court_chemin
} // namespace Algorithme


#endif // BELLMANFORD_GUARD