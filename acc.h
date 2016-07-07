#ifndef ACC_GUARD
#define ACC_GUARD

#ifndef GRAPHE_VALUE_GUARD
	#include "graphe_value.h"
	#include "graphe_value.cpp"
#endif

//#include <ctime>
#include <chrono>

namespace Algorithme
{
	namespace Court_chemin
	{
			// ---------------------------------------------------------
			// ------------ Algorithme court chemin --------------------
			// ---------------------------------------------------------

			template<class TA, class TS> class ACC
			{
			public:
				enum Type { 
					DIJKSTRA = 1, 
					BELLMAN_FORD, 
					ROY_FLOYD_WARSHALL 
				};

				/*
					MINIMUM =  tout les plus court chemins qui on la meme distance(petit distance trouvé) 
					TOUT	=  tout les chemins possible dans un graphe
				*/
				enum Type_parcour { 
					MINIMUM = 1, 
					TOUT 
				};

				// la valeur de la distance du plus cours chemin pris
				virtual TA distance_dl_source_vers(Sommet<TS> destinataire) const;

				// afficher le chemin pris dans n'importe quel sortie (output)
				virtual void afficher_parcour_dl_source_vers(Sommet<TS> destinataire, std::ostream& os) const;

				// avoir le chemin pris de la source vers le destinataire
				virtual std::vector< Sommet<TS> > parcour_dl_source_vers(Sommet<TS> destinataire) const;

				/*
					- tout autre chemins selon le type de parcour choisi
					- cet fonction ne gere pas les cycle entre pair de sommet
				*/
				virtual std::vector < std::pair< std::vector< Sommet<TS> >, TA > > autre_parcour_dl_source_vers(
					Sommet<TS> destinataire, Type a, Type_parcour tp) const;
				
				// presentation du resultat obtenu sous forme de tableau
				virtual void afficher_trace(Type a) const;
				virtual std::vector< std::vector<TA> > trace() const;

				// temp de calcule d'un algorithme
				virtual std::chrono::duration<uint, std::micro>::rep temp_execution_microseconds() const;
				virtual std::chrono::duration<uint, std::milli>::rep temp_execution_milliseconds() const;
				virtual std::chrono::duration<uint>::rep temp_execution_seconds() const;

				virtual ~ACC() { }

			protected:
				ACC(Graphe_value<TA, TS> graphe, Sommet<TS> source);
				Graphe_value<TA, TS> m_graphe;
				std::vector<TA> m_dist;
				const Sommet<TS> m_source;
				std::vector<int> m_parent;
				std::vector< std::vector<TA> > m_trace;

				std::chrono::system_clock::time_point m_debut_exec;
				std::chrono::system_clock::time_point m_fin_exec;

			protected:
				virtual void init_distance() = 0;
				virtual void calcule_distance() = 0;

			private:
				ACC(const ACC&);
				ACC& operator=(const ACC&);
			};
	} // namespace Court_chemin
} // namespace Algorithme

#endif // ACC_GUARD
