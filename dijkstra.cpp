#include "dijkstra.h"

namespace Algorithme
{
	namespace Court_chemin
	{
			template<class TA, class TS>
			Dijkstra<TA, TS>::Dijkstra(Graphe_value<TA, TS> g, Sommet<TS> s)
				: ACC(g, s), m_marque(m_graphe.nombre_sommet())
			{
				//debut de calcule
				m_debut_exec = std::chrono::system_clock::now();

				if (poid_negative())
					throw std::runtime_error("Algorithme de Dijkstra ne gere pas les poids negatives");
				init_distance();
				calcule_distance();

				//fin de calcule
				m_fin_exec = std::chrono::system_clock::now();
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			bool Dijkstra<TA, TS>::poid_negative() const
			{
				for (uint i = 0; i < m_graphe.nombre_arc(); ++i)
					if (m_graphe.list_arcs()[i].poid() < 0)
						return true;
				return false;
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			void Dijkstra<TA, TS>::init_distance()
			{
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i) {
					m_dist[i] = std::numeric_limits<TA>::max();
					m_parent[i] = -1;
					m_marque[i] = false;
				}
				m_dist[m_graphe.position_sommet(m_source)] = 0;
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			uint Dijkstra<TA, TS>::min_distance()
			{
				TA min = std::numeric_limits<TA>::max();
				uint min_index;

				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i)
					if (m_marque[i] == false && m_dist[i] <= min) {
						min = m_dist[i];
						min_index = i;
					}

				return min_index;
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			void Dijkstra<TA, TS>::calcule_distance()
			{
				std::vector<TA> vv; vv.push_back(std::numeric_limits<TA>::max());
				m_trace.push_back(vv);
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i)
					m_trace[m_trace.size() - 1].push_back(m_dist[i]);
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i) {
					uint u = min_distance();
					m_marque[u] = true;
					std::vector<TA> vv; vv.push_back(u); // indice du sommet a fixé
					m_trace.push_back(vv);

					for (uint v = 0; v < m_graphe.nombre_sommet(); ++v) {
						TA poid = trouver_poid(u, v);
						if (!m_marque[v] && poid != -1 && m_dist[u] != std::numeric_limits<TA>::max()
							&& m_dist[u] + poid < m_dist[v]){
							m_dist[v] = m_dist[u] + poid;
							m_parent[v] = u;
						}
					}
					// le tracé de chaque sommet fixé
					for (uint k = 0; k < m_dist.size(); ++k)
						m_trace[m_trace.size() - 1].push_back(m_dist[k]);
				}
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			TA Dijkstra<TA, TS>::trouver_poid(uint u, uint v) const
			{
				TA val = std::numeric_limits<TA>::max();
				for (uint i = 0; i < m_graphe.nombre_arc(); ++i)
					if (m_graphe.list_arcs()[i].sommet_initial() == m_graphe.list_successeur()[u][0] &&
						m_graphe.list_arcs()[i].sommet_final() == m_graphe.list_successeur()[v][0] &&
						m_graphe.list_arcs()[i].poid() < val)
						val = m_graphe.list_arcs()[i].poid();
				return val == std::numeric_limits<TA>::max() ? -1 : val;
			}
	} // namespace Court_chemin
} // namespace Algorithme