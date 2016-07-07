#include "acc.h"

namespace Algorithme
{
	namespace Court_chemin
	{
			template<class TA, class TS>
			ACC<TA, TS>::ACC(Graphe_value<TA, TS> graphe, Sommet<TS> source)
				: m_graphe(graphe), m_source(source),
				  m_dist(m_graphe.nombre_sommet()),
				  m_parent(m_graphe.nombre_sommet())
			{
				//m_graphe.aranger();
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			std::vector< Sommet<TS> > ACC<TA, TS>::parcour_dl_source_vers(Sommet<TS> dest) const
			{
				std::vector< Sommet<TS> > v;
				v.push_back(Sommet<TS>(dest));
				for (uint i = m_graphe.position_sommet(dest); m_parent[i] != -1;
					i = m_graphe.position_sommet(m_graphe.list_successeur()[m_parent[i]][0]))
				{
					v.push_back(m_graphe.list_successeur()[m_parent[i]][0]);
				}

				std::reverse(v.begin(), v.end());

				return v;
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			TA ACC<TA, TS>::distance_dl_source_vers(Sommet<TS> d) const
			{
				if (std::numeric_limits<TA>::max() == m_dist[m_graphe.position_sommet(d)])
					throw std::runtime_error("Ya pas de chemin entre (" + to_string(m_source) + ") et (" + to_string(d) + ")");
				return m_dist[m_graphe.position_sommet(d)];
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			void ACC<TA, TS>::afficher_parcour_dl_source_vers(Sommet<TS> dest, std::ostream& os) const
			{
				std::vector< Graphe::Sommet<std::string> > v(parcour_dl_source_vers(dest));
				for (uint i = 0; i < v.size(); ++i) {
					os << v[i];
					if (i != v.size() - 1)
						os << " -> ";
				}
				os << '\n';
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			void ACC<TA, TS>::afficher_trace(Type a) const
			{
				if (a == Type::DIJKSTRA) std::cout << "Fix";
				for (uint i = 0; i < m_graphe.nombre_sommet(); ++i)
					std::cout << std::setw(15) << m_graphe.list_successeur()[i][0];
				std::cout << '\n';
				for (uint i = 0; i < m_trace.size(); ++i) {
					if (a == Type::DIJKSTRA) {
						if (m_trace[i][0] == std::numeric_limits<TA>::max())
							std::cout << " ";
						else
							std::cout << m_graphe.list_successeur()[(int)m_trace[i][0]][0];
					}
					else if (a == Type::BELLMAN_FORD) {
						std::cout << " ";
					}
					for (uint j = 1; j < m_trace[i].size(); ++j) {
						if (m_trace[i][j] == std::numeric_limits<TA>::max())
							std::cout << std::setw(15) << "INF";
						else
							std::cout << std::setw(15) << m_trace[i][j];
					}
					std::cout << '\n';
				}
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			inline std::vector< std::vector<TA> > ACC<TA, TS>::trace() const
			{
				return m_trace;
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			inline std::chrono::duration<uint, std::micro>::rep ACC<TA, TS>::temp_execution_microseconds() const
				// temp de calcule d'un algorithme en microsecond
			{
				return std::chrono::duration_cast<std::chrono::microseconds>(m_fin_exec - m_debut_exec).count();
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			inline std::chrono::duration<uint, std::milli>::rep ACC<TA, TS>::temp_execution_milliseconds() const
				// temp de calcule d'un algorithme en millisecond
			{
				return std::chrono::duration_cast<std::chrono::milliseconds>(m_fin_exec - m_debut_exec).count();
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			inline std::chrono::duration<uint>::rep ACC<TA, TS>::temp_execution_seconds() const
				// temp de calcule d'un algorithme en second
			{
				return std::chrono::duration_cast<std::chrono::seconds>(m_fin_exec - m_debut_exec).count();
			}

			// ---------------------------------------------------------

			template<class TA, class TS>
			bool arc_par_ordre_croissant(std::pair< std::vector< Sommet<TS> >, TA > a, std::pair< std::vector< Sommet<TS> >, TA > b)
			{
				return a.second < b.second;
			}

			// --------------------------------------------------------

			template<class TA, class TS>
			std::vector < std::pair< std::vector< Sommet<TS> >, TA > >
				ACC<TA, TS>::autre_parcour_dl_source_vers(Sommet<TS> destinataire, Type a, Type_parcour tp) const
			{
				Graphe_value<TA, TS> graphe_partiel = m_graphe;
				graphe_partiel.set_type(Graphe_value<TA, TS>::Type::ORIENTE);
				uint u = 0, v = 0;
				std::vector < std::pair< std::vector< Sommet<TS> >, TA > > parcours;
				std::vector< Sommet<TS> > parcour_courant = parcour_dl_source_vers(destinataire);
				parcours.push_back(std::make_pair(parcour_courant, distance_dl_source_vers(destinataire)));
				// tout lien contenant le destinataire comme sommet final
				uint tsfd = 0; // suiveur de tout_sf_dest conteneur
				std::vector < Graphe::Arc<TA, TS> > tout_sf_dest;
				// tout lien qui ne contient pas de destinataire comme sommet final
				uint tsfnd = 0; // suiveur de tout_sf_non_dest conteneur
				std::vector < Graphe::Arc<TA, TS> > tout_sf_non_dest;
				std::vector < Graphe::Arc<TA, TS> > aide_tsfnd;
				// tout lien qui contien le sommet source comme sommet initial
				uint tsis = 0;
				std::vector < Graphe::Arc<TA, TS> > tout_si_src;

				for (uint i = 0; i < m_graphe.list_arcs().size(); ++i) {
					if (m_graphe.list_arcs()[i].sommet_final() == destinataire)
						tout_sf_dest.push_back(m_graphe.list_arcs()[i]);
					if (m_graphe.list_arcs()[i].sommet_initial() == m_source)
						tout_si_src.push_back(m_graphe.list_arcs()[i]);
					if (!(m_graphe.list_arcs()[i].sommet_final() == destinataire || 
						m_graphe.list_arcs()[i].sommet_initial() == m_source))
						tout_sf_non_dest.push_back(m_graphe.list_arcs()[i]);
				}

				// ya qu'un sommet qui separ le sommet source
				// du sommet destinataire
				if (tout_sf_non_dest.size() == 0) {
					for (uint i = 1; i < parcour_courant.size(); ++i) {
						for (uint j = 0; j < tout_sf_dest.size(); ++j) {
							if (parcour_courant[i - 1] == tout_sf_dest[j].sommet_initial() &&
								parcour_courant[i] == tout_sf_dest[j].sommet_final() &&
								distance_dl_source_vers(destinataire) == tout_sf_dest[j].poid()) {
								tout_sf_dest.erase(tout_sf_dest.begin() + j);
								break;
							}
						}
						for (uint j = 0; j < tout_si_src.size(); ++j) {
							if (parcour_courant[i - 1] == tout_si_src[j].sommet_initial() &&
								parcour_courant[i] == tout_si_src[j].sommet_final() &&
								distance_dl_source_vers(destinataire) == tout_si_src[j].poid()) {
								tout_si_src.erase(tout_si_src.begin() + j);
								break;
							}
						}
					}

					for (uint i = 0; i < tout_si_src.size(); ++i) {
						TA value = TA();
						for (uint j = 0; j < tout_sf_dest.size(); ++j) {
							value = tout_si_src[i].poid();
							if (tout_si_src[i].sommet_final() ==
								tout_sf_dest[j].sommet_initial()) {
								value += tout_sf_dest[j].poid();
								parcour_courant.clear();
								parcour_courant.push_back(tout_si_src[i].sommet_initial());
								parcour_courant.push_back(tout_si_src[i].sommet_final());
								parcour_courant.push_back(tout_sf_dest[j].sommet_final());
								if (tp == MINIMUM && value == distance_dl_source_vers(destinataire)) {
									parcours.push_back(std::make_pair(parcour_courant, value));
								}
								else if (tp == TOUT && value != distance_dl_source_vers(destinataire)) {
									parcours.push_back(std::make_pair(parcour_courant, value));
								}
							}
							else if (tout_si_src[i].sommet_initial() ==
								tout_sf_dest[j].sommet_initial() &&
								tout_si_src[i].sommet_final() ==
								tout_sf_dest[j].sommet_final()) {
								parcour_courant.clear();
								parcour_courant.push_back(tout_si_src[i].sommet_initial());
								parcour_courant.push_back(tout_si_src[i].sommet_final());
								if (tp == MINIMUM && value == distance_dl_source_vers(destinataire)) {
									parcours.push_back(std::make_pair(parcour_courant, value));
								}
								else if (tp == TOUT && value != distance_dl_source_vers(destinataire)) {
									parcours.push_back(std::make_pair(parcour_courant, value));
								}
							}

						}
					}
				}
				else {

					ACC<TA, TS>* bf = NULL;
					bool saute = false;

					// ne pas laissez de lien direct entre le sommet source 
					// et le sommet destinataire
					for (uint i = 0; i < tout_sf_dest.size(); ++i)
						graphe_partiel.del_arc(tout_sf_dest[i]);
					for (uint i = 0; i < tout_si_src.size(); ++i)
						graphe_partiel.del_arc(tout_si_src[i]);

					for (tsfd = 0; tsfd < tout_sf_dest.size(); ++tsfd) {
						graphe_partiel.add_arc(tout_sf_dest[tsfd]);
						for (tsis = 0; tsis < tout_si_src.size(); ++tsis) {
							graphe_partiel.add_arc(tout_si_src[tsis]);
							bool non_del = true, non_add = true;
							for (tsfnd = 0; tsfnd < tout_sf_non_dest.size(); ++tsfnd) {
								if (non_del) non_del = false;
								else graphe_partiel.del_arc(tout_sf_non_dest[tsfnd]);
								if (bf) { delete bf; bf = NULL; }
								if (a == Type::DIJKSTRA)
									bf = new Algorithme::Court_chemin::Dijkstra<TA, TS>(graphe_partiel, m_source);
								else if (a == Type::BELLMAN_FORD)
									bf = new Algorithme::Court_chemin::BellmanFord<TA, TS>(graphe_partiel, m_source);
								else if (a == Type::ROY_FLOYD_WARSHALL)
									bf = new Algorithme::Court_chemin::BellmanFord<TA, TS>(graphe_partiel, m_source);
								try {
									parcour_courant.clear();
									parcour_courant = bf->parcour_dl_source_vers(destinataire);

									if (parcour_courant.size() > 1) {
										bool add = true;
										for (uint q = 0, g; q < parcours.size() && add; ++q) {
											if (parcours[q].first.size() != parcour_courant.size());
											else {
												for (g = 0; g < parcours[q].first.size(); ++g) {
													if (parcours[q].first[g] != parcour_courant[g] ||
														parcours[q].second != bf->distance_dl_source_vers(destinataire))
														break;
												}
												if (g == parcour_courant.size())
													add = false;
											}
										}
										if (add) {
											if (tp == TOUT && bf->distance_dl_source_vers(destinataire) !=
												distance_dl_source_vers(destinataire))
												parcours.push_back(std::make_pair(parcour_courant,
												bf->distance_dl_source_vers(destinataire)));
											else if (tp == MINIMUM && bf->distance_dl_source_vers(destinataire) ==
												distance_dl_source_vers(destinataire))
												parcours.push_back(std::make_pair(parcour_courant,
												bf->distance_dl_source_vers(destinataire)));
										}
									}
								}
								catch (std::exception) {
								}
								if (non_add) { non_add = false; --tsfnd; }
								else graphe_partiel.add_arc(tout_sf_non_dest[tsfnd]);
							}
							graphe_partiel.del_arc(tout_si_src[tsis]);
						}
						graphe_partiel.del_arc(tout_sf_dest[tsfd]);
					}
				}

				parcours.erase(parcours.begin());

				if (tp == TOUT)
					std::sort(parcours.begin(), parcours.end(), arc_par_ordre_croissant<TA, TS>);

				return parcours;
			}
	} // namespace Court_chemin
} // namespace Algorithme