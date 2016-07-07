#include "graphe_value.h"

template<class TA, class TS>
Graphe_value<TA, TS>::Graphe_value(Type t)
	: m_oriente((t == Graphe_value::ORIENTE ? true : false))
{
}

// ---------------------------------------------------------

template<class TA, class TS>
inline bool Graphe_value<TA, TS>::oriente() const
{
	return m_oriente;
}

// ---------------------------------------------------------

template<class TA, class TS>
inline bool Graphe_value<TA, TS>::non_oriente() const
{
	return !m_oriente;
}

// ---------------------------------------------------------

template<class TA, class TS>
Graphe_value<TA, TS>::~Graphe_value() { }

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::add_sommet(Sommet<TS> s)
{
	for (uint i = 0; i < m_ls.size(); ++i)
		if (m_ls[i][0] == s) // le sommet existe deja
			return;
	std::vector< Graphe::Sommet<TS> > ls;
	ls.push_back(s);
	m_ls.push_back(ls);
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::mod_sommet(Sommet<TS> s, Sommet<TS> n)
{
	for (uint i = 0; i < m_ls.size(); ++i)
		for (uint j = 0; j < m_ls[i].size(); ++j)
			if (m_ls[i][j] == s) {
				m_ls[i][j] = n;
				m_ls[i][j].position(n.position());
			}
	for (uint i = 0; i < m_arc.size(); ++i)
		if (m_arc[i].sommets().first == s && m_arc[i].sommets().second == s) 
			m_arc[i].sommets(std::make_pair(n, n));
		else if (m_arc[i].sommets().first == s)
			m_arc[i].sommets(std::make_pair(n, m_arc[i].sommets().second));
		else if (m_arc[i].sommets().second == s)
			m_arc[i].sommets(std::make_pair(m_arc[i].sommets().first, n));
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::del_sommet(Sommet<TS> s)
{
	/*
	typedef typename List_successeur::iterator Iter;
	for (Iter i = m_ls.begin(); i != m_ls.end(); ++i)
		if (*(*i) == s)
			m_ls.erase(i);
	*/

	for (uint i = 0; i < m_ls.size(); ++i)
		if (m_ls[i][0] == s)
			m_ls.erase(m_ls.begin() + i);

	for (uint i = 0; i < m_ls.size(); ++i)
		for (uint j = 1; j < m_ls[i].size(); ++j)
			if (m_ls[i][j] == s) {
				m_ls[i].erase(m_ls[i].begin() + j);
				--j;
			}

	// supprimer les arete/arc qui sont lié au sommet s
	for (uint i = 0; i < m_arc.size(); ++i)
		if (m_arc[i].sommets().first == s ||
			m_arc[i].sommets().second == s)
		{
			m_arc.erase(m_arc.begin() + i);
			--i;
		}
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::add_arc(Graphe::Arc<TA, TS> a)
{
	if (non_oriente())
		throw std::runtime_error("Graphe<NON_ORIENTE> utilisez les aretes...");

	add_sommet(a.sommet_initial());
	add_sommet(a.sommet_final());

	bool ok = true;
	for (uint i = 0; i < m_ls.size(); ++i) {
		ok = true;
		if (m_ls[i][0] == a.sommet_initial()) {
			for (uint j = 1; j < m_ls[i].size(); ++j)
				if (m_ls[i][j] == a.sommet_final()) {
					ok = false;
					break;
				}
			if (ok)
				m_ls[i].push_back(a.sommet_final());
		}
	}

	m_arc.push_back(a);
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::del_arc(Graphe::Arc<TA, TS> a)
{
	for (uint i = 0; i < m_arc.size(); ++i)
		if (m_arc[i] == a && m_arc[i].sommet_initial() == a.sommet_initial()
			&& m_arc[i].sommet_final() == a.sommet_final())
		{
			m_arc.erase(m_arc.begin() + i);
			break;
		}

	for (uint i = 0; i < m_ls.size(); ++i)
		if (m_ls[i][0] == a.sommet_initial())
			for (uint j = 1; j < m_ls[i].size(); ++j)
				if (m_ls[i][j] == a.sommet_final()) {
					m_ls[i].erase(m_ls[i].begin() + j);
					return;
				}
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::add_arete(Arete<TA, TS> a)
{
	if (oriente())
		throw std::runtime_error("Graphe<ORIENTE> utilisez les arcs...");

	add_sommet(a.sommets().first);
	add_sommet(a.sommets().second);

	bool ok = true;

	for (uint i = 0; i < m_ls.size(); ++i) {
		ok = true;
		if (m_ls[i][0] == a.sommets().first) {
			for (uint j = 1; j < m_ls[i].size(); ++j)
				if (m_ls[i][j] == a.sommets().second) {
					ok = false;
					break;
				}
			if (ok) m_ls[i].push_back(a.sommets().second);
		}
		else if (m_ls[i][0] == a.sommets().second) {
			for (uint j = 1; j < m_ls[i].size(); ++j)
				if (m_ls[i][j] == a.sommets().first) {
					ok = false;
					break;
				}
			if (ok) m_ls[i].push_back(a.sommets().first);
		}
	}

	m_arc.push_back(Graphe::Arc<TA, TS>(a.poid(), a.sommets().first, a.sommets().second));
	m_arc.push_back(Graphe::Arc<TA, TS>(a.poid(), a.sommets().second, a.sommets().first));
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::del_arete(Arete<TA, TS> a)
{
	for (uint i = 0, j = 0; i < m_arc.size(); ++i)
		if (m_arc[i] == a && (m_arc[i].sommets().first == a.sommets().first
			|| m_arc[i].sommets().first == a.sommets().second)
			&& (m_arc[i].sommets().second == a.sommets().second
			|| m_arc[i].sommets().second == a.sommets().first))
		{
			m_arc.erase(m_arc.begin() + i);
			--i;
			++j;
			if (j == 2) break;
		}

	for (uint i = 0; i < m_ls.size(); ++i) {
		if (m_ls[i][0] == a.sommets().first) {
			for (uint j = 1; j < m_ls[i].size(); ++j) {
				if (m_ls[i][j] == a.sommets().second) {
					m_ls[i].erase(m_ls[i].begin() + j);
				}
			}
		}
		else if (m_ls[i][0] == a.sommets().second) {
			for (uint j = 1; j < m_ls[i].size(); ++j) {
				if (m_ls[i][j] == a.sommets().first) {
					m_ls[i].erase(m_ls[i].begin() + j);
				}
			}
		}
	}
}

// ---------------------------------------------------------

template<class TA, class TS>
void Graphe_value<TA, TS>::mod_lien(Graphe::Arc<TA, TS> a, TA np)
{
	for (uint i = 0; i < m_arc.size(); ++i)
		if (a.sommets().first == m_arc[i].sommets().first &&
			a.sommets().second == m_arc[i].sommets().second &&
			a == m_arc[i]) 
		{
			m_arc[i].set_poid(np);
			break;
		}
}

// ---------------------------------------------------------

template<class TA, class TS>
inline uint Graphe_value<TA, TS>::nombre_sommet() const
{
	return m_ls.size();
}

// ---------------------------------------------------------

template<class TA, class TS>
inline uint Graphe_value<TA, TS>::nombre_arc() const
{
	/*if (non_oriente())
	throw std::runtime_error("Graphe<NON_ORIENTE> utilisez nombre_arete()...");*/
	// les aretes peuvent etre represente en deux arc inverse
	return m_arc.size();
}

// ---------------------------------------------------------

template<class TA, class TS>
inline uint Graphe_value<TA, TS>::nombre_arete() const
{
	if (oriente())
		throw std::runtime_error("Graphe<ORIENTE> utilisez nombre_arc()...");
	return m_arc.size() / 2;
}

// ---------------------------------------------------------

template<class TA, class TS>
Graphe_value<TA, TS>& Graphe_value<TA, TS>::operator=(const Graphe_value<TA, TS>& b)
{
	if (this == &b) return *this;

	if (m_ls.size() < b.m_ls.size()) m_ls.resize(b.m_ls.size());
	for (uint i = 0; i < b.m_ls.size(); ++i) {
		if (m_ls[i].size() < b.m_ls[i].size())
			m_ls[i].resize(b.m_ls[i].size());
		copy(b.m_ls[i].begin(), b.m_ls[i].end(), m_ls[i].begin());
	}

	if (m_arc.size() < b.m_arc.size())
		m_arc.resize(b.m_arc.size());
	copy(b.m_arc.begin(), b.m_arc.end(), m_arc.begin());

	m_oriente = b.m_oriente;

	return *this;
}

// ---------------------------------------------------------

template<class TA, class TS>
Graphe_value<TA, TS>::Graphe_value(const Graphe_value& b)
{
	m_ls.resize(b.m_ls.size());
	for (uint i = 0; i < b.m_ls.size(); ++i) {
		m_ls[i].resize(b.m_ls[i].size());
		copy(b.m_ls[i].begin(), b.m_ls[i].end(), m_ls[i].begin());
	}

	for (uint i = 0; i < b.m_arc.size(); ++i)
		m_arc.push_back(b.m_arc[i]);

	m_oriente = b.m_oriente;
}

// ---------------------------------------------------------

template<class TA, class TS>
inline const typename Graphe_value<TA, TS>::List_arc& Graphe_value<TA, TS>::list_arcs() const
{
	return m_arc;
}

// ---------------------------------------------------------

template<class TA, class TS>
inline const typename Graphe_value<TA, TS>::List_successeur& Graphe_value<TA, TS>::list_successeur() const
{
	return m_ls;
}

// ---------------------------------------------------------

template<class TA, class TS>
uint Graphe_value<TA, TS>::position_sommet(Sommet<TS> s) const
{
	for (uint i = 0; i < nombre_sommet(); ++i)
		if (s == m_ls[i][0])
			return i;

	throw std::runtime_error("sommet (" + to_string(s) + ") n'existe pas");
}

template<class TA, class TS>
void Graphe_value<TA, TS>::dessiner(wxDC& dc, wxPen lien, wxPen sommet, bool afficher_poid)
{
	dc.SetPen(sommet);
	for (uint i = 0; i < m_ls.size(); ++i) m_ls[i][0].dessiner(dc, i);
	dc.SetPen(lien);

	int v = oriente() ? 1 : 2;
	uint count = 1;
	for (uint i = 0; i < m_arc.size(); i+=v) {
		count = 1;
		if (i != 0)
			for (uint j = i - v; j >= 0; j-=v) {
				if (m_arc[j].sommet_initial() == m_arc[i].sommet_initial() &&
					m_arc[j].sommet_final() == m_arc[i].sommet_final())
					count += 2;
				if (j == 0) break;
			}
		if (v == 1) m_arc[i].dessiner(dc, afficher_poid, count);
		else ((Arete<TA, TS>)m_arc[i]).dessiner(dc, afficher_poid, count);
	}
}

// ---------------------------------------------------------

template<class TA, class TS>
inline void Graphe_value<TA, TS>::set_type(Type t)
{
	m_oriente = (t == Type::ORIENTE ? true : false);
}

// ---------------------------------------------------------

/*template<class TA, class TS>
void Graphe_value<TA, TS>::aranger()
{
	std::sort(m_arc.begin(), m_arc.end());
}*/

// ---------------------------------------------------------

template<class TA, class TS>
std::vector< std::vector<int> >  Graphe_value<TA, TS>::matrice_adjacence() const
{
	if (m_ls.size() == 0)
		throw std::runtime_error("Ya pas de graphe pour le represente sous forme de matrice d'adjacence");
	int count = 0;
	std::vector< std::vector<int> > ma(m_ls.size(), std::vector<int>(m_ls.size(), 0));
	for (uint i = 0; i < ma.size(); ++i) {
		for (uint j = 0; j < ma.size(); ++j) {
			count = 0;
			for (int k = 0; k < m_arc.size(); ++k) {
				if (m_arc[k].sommets().first == m_ls[i][0] &&
					m_arc[k].sommets().second == m_ls[j][0]) {
					++count;
					if (m_ls[i][0] == m_ls[j][0] && !m_oriente) ++k;
				}
			}
			ma[i][j] = count;
		}
	}

	return ma;
}

template<class TA, class TS>
std::vector< std::vector<int> >  Graphe_value<TA, TS>::matrice_incidence() const
{
	if (m_ls.size() == 0)
		throw std::runtime_error("Ya pas de graphe pour le represente sous forme de matrice d'incidence");
	int count = 0;
	std::vector< std::vector<int> > ma(m_ls.size(), std::vector<int>(m_oriente ? m_arc.size() : m_arc.size()/2, 0));
	
	if (m_oriente)
		for (uint i = 0; i < m_ls.size(); ++i) {
			for (uint j = 0; j < m_arc.size(); ++j) {
				if (m_arc[j].sommet_initial() == m_ls[i][0] &&
					m_arc[j].sommet_final() == m_ls[i][0]) ma[i][j] = -2;
				else if (m_arc[j].sommet_initial() == m_ls[i][0]) ma[i][j] = 1;
				else if (m_arc[j].sommet_final() == m_ls[i][0]) ma[i][j] = -1;
			}
		}
	else
		for (uint i = 0; i < m_ls.size(); ++i) {
			for (uint j = 0, k = 0; j < m_arc.size(); j+=2, ++k) {
				if (m_arc[j].sommets().first == m_ls[i][0] &&
					m_arc[j].sommets().second == m_ls[i][0]) ma[i][k] = -2;
				else if (m_arc[j].sommets().first == m_ls[i][0] || 
					m_arc[j].sommets().second == m_ls[i][0]) ma[i][k] = 1;
			}
		}

	return ma;
}

template<class TA, class TS>
std::vector< std::vector<TA> >  Graphe_value<TA, TS>::matrice_valuation() const
{
	if (m_ls.size() == 0)
		throw std::runtime_error("Ya pas de graphe pour le represente sous forme de matrice de valuation");
	std::vector< std::vector<TA> > mv(m_ls.size(), std::vector<TA>(m_ls.size(), std::numeric_limits<TA>::max()));
	for (uint i = 0; i < m_ls.size(); ++i) {
		for (uint j = 0; j < m_ls.size(); ++j) {
			TA min = std::numeric_limits<TA>::max();
			for (uint k = 0; k < m_arc.size(); ++k) {
				if (m_ls[i][0] == m_arc[k].sommets().first &&
					m_ls[j][0] == m_arc[k].sommets().second &&
					m_arc[k].poid() < min)
					min = m_arc[k].poid();
			}
			if (i == j && min == std::numeric_limits<TA>::max())
				mv[i][j] = 0;
			else	
				mv[i][j] = min;
		}
	}
	return mv;
}
