#include "roy_floyd_warshall.h"

namespace Algorithme
{
	namespace Court_chemin
	{
		template<class TA, class TS>
		Roy_floyd_warshall<TA, TS>::Roy_floyd_warshall(Graphe_value<TA, TS> g, Sommet<TS> s)
			: ACC(g, s), m_graphe_matrice(g.nombre_sommet(), std::vector<TA>(g.nombre_sommet())),
			m_dist_matrice(g.nombre_sommet(), std::vector<TA>(g.nombre_sommet())),
			m_parent_matrice(g.nombre_sommet(), std::vector<TA>(g.nombre_sommet()))
		{
			// debut
			m_debut_exec = std::chrono::system_clock::now();

			init_distance();
			calcule_distance();

			// fin
			m_fin_exec = std::chrono::system_clock::now();
		}

		// ---------------------------------------------------------

		template<class TA, class TS>
		void Roy_floyd_warshall<TA, TS>::init_distance()
			// initialiser distance 
		{
			bool ok = false;
			for (uint i = 0; i < m_graphe_matrice.size(); ++i) {
				for (uint j = 0; j < m_graphe_matrice[i].size(); ++j) {
					ok = false;
					if (i == j) {
						m_graphe_matrice[i][j] = 0;
						m_parent_matrice[i][j] = i;
						continue;
					}
					else {
						m_graphe_matrice[i][j] = std::numeric_limits<TA>::max();
						for (uint k = 0; k < m_graphe.nombre_arc(); ++k)
							if (m_graphe.list_arcs()[k].sommet_initial() == m_graphe.list_successeur()[i][0] &&
								m_graphe.list_arcs()[k].sommet_final() == m_graphe.list_successeur()[j][0] &&
								m_graphe.list_arcs()[k].poid() < m_graphe_matrice[i][j]) {
								m_graphe_matrice[i][j] = m_graphe.list_arcs()[k].poid();
								m_parent_matrice[i][j] = i;
								ok = true;
							}
					}
					if (!ok) {
						// ya pas de lien entre i et j
						m_graphe_matrice[i][j] = std::numeric_limits<TA>::max(); // infini
						m_parent_matrice[i][j] = -1; // vide
					}
				}
			}

			for (uint i = 0; i < m_graphe_matrice.size(); ++i)
				for (uint j = 0; j < m_graphe_matrice[i].size(); ++j)
					m_dist_matrice[i][j] = m_graphe_matrice[i][j];
		}

		// ---------------------------------------------------------

		template<class TA, class TS>
		void Roy_floyd_warshall<TA, TS>::calcule_distance()
			// calcule du plus court chemin entre la source et les autres sommets( |nombre_sommet| - 1 )
		{
			for (uint k = 0; k < m_graphe.nombre_sommet(); ++k) {
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i) {
					for (uint j = 0; j < m_graphe.nombre_sommet(); ++j) {
						if (m_dist_matrice[i][k] + m_dist_matrice[k][j] < m_dist_matrice[i][j]) {
							m_dist_matrice[i][j] = m_dist_matrice[i][k] + m_dist_matrice[k][j];
							m_parent_matrice[i][j] = m_parent_matrice[k][j];
						}
						if (i == j && m_dist_matrice[i][j] < 0)
							if (m_graphe.non_oriente())
								throw std::runtime_error("Graphe contient un cycle negative\n");
							else
								throw std::runtime_error("Graphe contient un circuit absorbant\n");
					}
				}
				m_trace_matrice.push_back(m_dist_matrice);
			}
		}

		// ---------------------------------------------------------

		template<class TA, class TS>
		const std::vector< std::vector< std::vector<TA> > >& Roy_floyd_warshall<TA, TS>::trace_matrice() const
		{
			return m_trace_matrice;
		}

		// ---------------------------------------------------------

		template<class TA, class TS>
		std::vector< std::vector<TA> > Roy_floyd_warshall<TA, TS>::trace() const
		{
			return m_dist_matrice;
		}

		// ---------------------------------------------------------

		template<class TA, class TS>
		TA Roy_floyd_warshall<TA, TS>::distance_dl_source_vers(Sommet<TS> d) const
			// la distance du plus cours chemin pris
		{
			if (std::numeric_limits<TA>::max() == m_dist_matrice[m_graphe.position_sommet(m_source)][m_graphe.position_sommet(d)])
				throw std::runtime_error("Ya pas de chemin entre (" + to_string(m_source) + ") et (" + to_string(d) + ")");
			return m_dist_matrice[m_graphe.position_sommet(m_source)][m_graphe.position_sommet(d)];
		}

		// ---------------------------------------------------------

		template<class TA, class TS>
		std::vector< Sommet<TS> > Roy_floyd_warshall<TA, TS>::parcour_dl_source_vers(Sommet<TS> dest) const
		{
			std::vector< Graphe::Sommet<TS> > v;

			uint i = m_graphe.position_sommet(m_source);
			uint j = m_graphe.position_sommet(dest);

			bool ok = false;

			if (i < j)
				while (m_parent_matrice[i][j] != m_graphe.position_sommet(m_source)) {
					v.push_back(m_graphe.list_successeur()[j][0]);
					j = m_parent_matrice[i][j];
				}
			else {
				int pred = j;
				while (m_parent_matrice[j][i] != m_graphe.position_sommet(m_source)) {
					v.push_back(m_graphe.list_successeur()[j][0]);
					pred = j;
					j = m_parent_matrice[j][i];
					if (m_parent_matrice[j][i] == m_parent_matrice[pred][i]) {
						ok = true;
						break;
					}
				}
			}
			if (ok) --j;
			v.push_back(m_graphe.list_successeur()[j][0]);
			v.push_back(m_graphe.list_successeur()[i][0]);
			std::reverse(v.begin(), v.end());
			if (v.size() >= 2 && v[v.size() - 1] == v[v.size() - 2])
				v.pop_back();
			return v;
		}
	} // namespace Court_chemin
} // namespace Algorithme