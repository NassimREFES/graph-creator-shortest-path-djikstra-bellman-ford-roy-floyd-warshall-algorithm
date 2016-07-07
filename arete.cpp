#include "arete.h"

namespace Graphe
{
	template<class T, class U>
	Arete<T, U >::Arete(T p, Sommet<U> s1, Sommet<U> s2)
		: m_poid(p), m_sommets(std::make_pair(s1, s2))
	{
	}

	// ---------------------------------------------------------

	template<class T, class U>
	Arete<T, U>::~Arete()
	{
		m_poid.~T();
		m_sommets.first.~Sommet<U>();
		m_sommets.second.~Sommet<U>();
	}

	// ---------------------------------------------------------

	template<class T, class U>
	inline void Arete<T, U>::set_poid(T np) { m_poid = np; }

	// ---------------------------------------------------------

	template<class T, class U>
	inline T Arete<T, U>::poid() const { return m_poid; }

	// ---------------------------------------------------------

	template<class T, class U>
	inline std::pair< Sommet<U>, Sommet<U> > Arete<T, U>::sommets() const
	{
		return m_sommets;
	}

	// ---------------------------------------------------------

	template<class T, class U>
	void Arete<T, U>::sommets(std::pair< Sommet<U>, Sommet<U> > s)
	{
		m_sommets.first.set(s.first.get());
		m_sommets.first.position(s.first.position());
		m_sommets.second.set(s.second.get());
		m_sommets.second.position(s.second.position());
	}

	// ---------------------------------------------------------

	template<class T, class U, class V>
	inline bool operator==(const Arete<T, U>& a1, const Arete<T, V>& a2)
	{
		return a1.poid() == a2.poid();
	}

	// ---------------------------------------------------------

	template<class T, class U, class V>
	inline bool operator<(const Arete<T, U>& a1, const Arete<T, V>& a2)
	{
		return a1.poid() < a2.poid();
	}

	template<class T, class U>
	double Arete<T, U>::dessiner(wxDC& dc, bool afficher_poid, int count)
	{	
		wxPoint a = m_sommets.first.position();
		wxPoint b = m_sommets.second.position();
		if (a == b && m_sommets.first == m_sommets.second) {
			// boucle
			wxPoint p1(a.x - rayon_sommet, a.y);
			wxPoint p2(a.x - (rayon_sommet * 2)*count - ((rayon_sommet * 2)*count)/3,
				a.y - (rayon_sommet * 2)*count - ((rayon_sommet * 2)*count)/3);
			wxPoint p3(a.x, a.y - rayon_sommet);
			wxPoint p4(a.x - rayon_sommet - (rayon_sommet)*count, a.y);
			wxPoint p5(a.x, a.y - rayon_sommet - (rayon_sommet)*count);
			wxPoint points[5] = { p1, p4, p2, p5, p3 };
			wxPoint pt(a.x - (rayon_sommet * 2)*count, a.y - (rayon_sommet * 2)*count);
			//dc.DrawSpline(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
			dc.DrawSpline(5, points);
			if (afficher_poid)
				dc.DrawText(to_string(m_poid), pt);
			return angle_par_defaut;
		}

		int signe = a.y < b.y ? 1 : -1; // pour ne pas faire un tour complet

		for (int i = 0; i <= 360*2; ++i) {
			wxPoint rp(Rotation::rotation_point(a, b, signe*(double)i));
			if (a.y-14 <= rp.y && rp.y <= a.y+14 && a.x < rp.x) {
				wxPoint ap(a.x + rayon_sommet, a.y);
				wxPoint bp(rp.x - rayon_sommet, rp.y);
				wxPoint tp(a.x + (rp.x - a.x) / 2, a.y + (20 * count));
				wxPoint tpp(a.x + (rp.x - a.x) / 2, a.y + (20 * count) + (20 * count) / 3);
				ap = Rotation::rotation_point(a, ap, -signe*i);
				bp = Rotation::rotation_point(a, bp, -signe*i);
				tp = Rotation::rotation_point(a, tp, -signe*i);
				tpp = Rotation::rotation_point(a, tpp, -signe*i);
				//dc.DrawLine(ap, bp);
				dc.DrawSpline(ap.x, ap.y, tpp.x, tpp.y, bp.x, bp.y);
				if (afficher_poid)
					dc.DrawText(to_string(m_poid), tp);
				return signe*i;
			}
		}
	}

	template<class T, class U>
	Arete<T, U>::Arete(const Arete<T, U>& a)
	{
		m_poid = a.m_poid;
		m_sommets.first = a.m_sommets.first;
		m_sommets.second = a.m_sommets.second;
	}

	template<class T, class U>
	Arete<T, U>& Arete<T, U>::operator=(const Arete<T, U>& a)
	{
		if (this == &a) return *this;
		m_poid = a.m_poid;
		m_sommets.first = a.m_sommets.first;
		m_sommets.second = a.m_sommets.second;
		return *this;
	}

	// ---------------------------------------------------------

	template<class T, class U> std::istream& operator>>(std::istream& is, Arete<T, U>& a)
	{
		T poid;
		U si, sf;
		char ch1 = 0, ch2 = 0;
		if (is >> ch1 && ch1 != '(') {
			is.unget();
			is.clear(std::ios_base::failbit);
			return is;
		}

		is >> poid >> si >> sf >> ch2;
		if (!is || ch2 != ')') throw std::runtime_error("mauvaise arc");

		a.set_poid(poid);
		a.sommets(std::make_pair(Sommet<U>(si), Sommet<U>(sf)));

		return is;
	}

} // namespace Graphe