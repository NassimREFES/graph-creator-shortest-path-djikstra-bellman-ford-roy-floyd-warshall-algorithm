#include "sommet.h"

namespace Graphe
{
	template<class T>
	std::ostream& operator<<(std::ostream& os, const Sommet<T>& s)
	{
		return os << s.get();
	}

	template<class T>
	std::istream& operator>>(std::istream& is, Sommet<T>& s)
	{
		T id;
		wxPoint pos;
		char ch1=0, ch2=0;
		if (is >> ch1 && ch1 != '(') {
			is.unget();
			is.clear(std::ios_base::failbit);
			return is;
		}

		is >> id >> pos.x >> pos.y >> ch2;
		if (!is || ch2 != ')') throw std::runtime_error("mauvais sommet");
		s.set(id);
		s.position(pos);

		return is;
	}

	// ---------------------------------------------------------

	template<class T>
	Sommet<T>::Sommet() : id(T()), pos(0, 0) { }

	// ---------------------------------------------------------

	template<class T>
	Sommet<T>::Sommet(T s) : id(s), pos(0, 0) { }

	// ---------------------------------------------------------

	template<class T>
	Sommet<T>::Sommet(T s, wxPoint p) : id(s), pos(p) { }

	// ---------------------------------------------------------

	template<class T>
	Sommet<T>::~Sommet() { id.~T(); }

	// ---------------------------------------------------------

	template<class T>
	inline void Sommet<T>::set(T ns) { id = ns; }

	// ---------------------------------------------------------

	template<class T>
	inline T Sommet<T>::get() const { return id; }

	// ---------------------------------------------------------

	template<class T>
	bool operator==(const Sommet<T>& a, const Sommet<T>& b)
	{
		return a.get() == b.get();
	}

	// ---------------------------------------------------------

	template<class T>
	bool operator!=(const Sommet<T>& a, const Sommet<T>& b)
	{
		return a.get() != b.get();
	}

	// ---------------------------------------------------------

	template<class T>
	bool operator<(const Sommet<T>& a, const Sommet<T>& b)
	{
		return a.get() < b.get();
	}

	// ---------------------------------------------------------

	template<class T>
	void Sommet<T>::position(wxPoint p)
	{
		pos = p;
	}

	// ---------------------------------------------------------

	template<class T>
	wxPoint Sommet<T>::position() const
	{
		return pos;
	}

	// ---------------------------------------------------------

	template<class T>
	void Sommet<T>::dessiner(wxDC& dc, uint i)
	{
		dc.DrawCircle(pos, rayon_sommet);
		dc.DrawText(wxString(to_string(id)).SubString(0, 2), wxPoint(pos.x - 8, pos.y - 6));
	}

} // namespace Graphe