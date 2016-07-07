#include "arc.h"

namespace Graphe
{
	template<class T, class U>
	Arc<T, U>::Arc(T p, Sommet<U> si, Sommet<U> sf)
		: Arete(p, si, sf)
	{
	}

	// ---------------------------------------------------------

	template<class T, class U>
	inline Sommet<U> Arc<T, U>::sommet_initial() const
	{
		return m_sommets.first;
	}

	// ---------------------------------------------------------

	template<class T, class U>
	inline Sommet<U> Arc<T, U>::sommet_final() const
	{
		return m_sommets.second;
	}

	// ---------------------------------------------------------

	template<class T, class U>
	void Arc<T, U>::dessiner(wxDC& dc, bool afficher_poid, int count)
	{
		double angle = Arete<T, U>::dessiner(dc, afficher_poid, count);
		wxPoint a = sommet_initial().position();
		wxPoint b = sommet_final().position();

		if (angle == angle_par_defaut) {
			wxPoint x1(a.x - rayon_sommet, a.y - rayon_sommet - rayon_sommet/3);
			wxPoint x2(a.x + rayon_sommet/3, a.y - rayon_sommet * 2);
			dc.DrawLine(x1, wxPoint(a.x, a.y - rayon_sommet));
			dc.DrawLine(x2, wxPoint(a.x, a.y - rayon_sommet));
			return;
		}

		/*
			* reglage de la fleche ( degré a decaler par raport au lien )
			--------------------------------------------------------------
		double distance = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
		double x = 0.2;

		if (450 <= distance && distance <= 800) x = 0.5;
		else if (250 <= distance && distance < 450) x = 1;
		else if (distance < 250) x = 2;

		*/

		wxPoint rp = Rotation::rotation_point(a, b, angle);
		rp = wxPoint(a.x + (rp.x - a.x) / 2, a.y + (20 * count));
		wxPoint x1, x2;
		x1 = x2 = wxPoint(rp.x - rayon_sommet/2, rp.y);
		x1 = Rotation::rotation_point(a, x1, -angle-2);
		x2 = Rotation::rotation_point(a, x2, -angle+2);
		rp = Rotation::rotation_point(a, rp, -angle);
		dc.DrawLine(x1, rp);
		dc.DrawLine(x2, rp);
	}
} // namespace Graphe