#include "bellmanford.h"

namespace Algorithme
{
	namespace Court_chemin
	{
			template<class TA, class TS>
			BellmanFord<TA, TS>::BellmanFord(Graphe_value<TA, TS> g, Sommet<TS> s)
				: ACC(g, s)
			{
				//debut de calcule
				m_debut_exec = std::chrono::system_clock::now();
				
				init_distance();
				calcule_distance();
				if (!cycle_negative()) {
					if (g.non_oriente())
						throw std::runtime_error("Graphe contient un cycle negative\n");
					else
						throw std::runtime_error("Graphe contient un circuit absorbant\n");
				}

				//fin de calcule
				m_fin_exec = std::chrono::system_clock::now();
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			void BellmanFord<TA, TS>::init_distance() 
			{
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i) {
					m_dist[i] = std::numeric_limits<TA>::max();
					m_parent[i] = -1;
				}
				m_dist[m_graphe.position_sommet(m_source)] = 0;
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			void BellmanFord<TA, TS>::calcule_distance()
			{
				std::vector<TA> vv; vv.push_back(std::numeric_limits<TA>::max());
				m_trace.push_back(vv);
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i)
					m_trace[m_trace.size() - 1].push_back(m_dist[i]);
				for (uint i = 1; i <= m_graphe.nombre_sommet() - 1; ++i) {
					for (uint j = 0; j < m_graphe.nombre_arc(); ++j) {
						uint u = m_graphe.position_sommet(m_graphe.list_arcs()[j].sommet_initial());
						uint v = m_graphe.position_sommet(m_graphe.list_arcs()[j].sommet_final());
						TA poid = m_graphe.list_arcs()[j].poid();
						if (m_dist[u] != std::numeric_limits<TA>::max()
							&& m_dist[u] + poid < m_dist[v]) {
							m_dist[v] = m_dist[u] + poid;
							if (poid < 0) {
								uint q = 0;
								for (; q < j; ++q) {
									if (m_graphe.list_arcs()[j].sommet_initial() == m_graphe.list_arcs()[q].sommet_final()
										&& m_graphe.list_arcs()[j].sommet_final() == m_graphe.list_arcs()[q].sommet_initial()) {
										break;
									}
								}
								if (q == j)
									m_parent[v] = u;
							}
							else
								m_parent[v] = u;

							// ------------------------------------
							std::vector<TA> vv; vv.push_back(j); // indice de l'iteration
							m_trace.push_back(vv);
							// le tracé
							for (uint k = 0; k < m_dist.size(); ++k)
								m_trace[m_trace.size() - 1].push_back(m_dist[k]);
						}
					}
				}
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			bool BellmanFord<TA, TS>::cycle_negative()
			{
				for (uint i = 0; i < m_graphe.nombre_arc(); ++i)
				{
					uint u = m_graphe.position_sommet(m_graphe.list_arcs()[i].sommet_initial());
					uint v = m_graphe.position_sommet(m_graphe.list_arcs()[i].sommet_final());
					TA poid = m_graphe.list_arcs()[i].poid();
					if (m_dist[u] != std::numeric_limits<TA>::max()
						&& m_dist[u] + poid < m_dist[v])
						return false;
					return true;
				}
			}
	} // namespace Court_chemin
} // namespace Algorithme