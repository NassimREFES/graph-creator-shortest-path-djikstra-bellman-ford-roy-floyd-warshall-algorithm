#ifndef GLOBAL_GUARD
#define GLOBAL_GUARD

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/textdlg.h>
	#include <wx/dcclient.h>
	#include <wx/frame.h>
	#include <wx/menu.h>
	#include <wx/toolbar.h>
	#include <wx/image.h>
	#include <wx/bitmap.h>
	#include <wx/colour.h>
	#include <wx/pen.h>
	#include <wx/brush.h>
	#include <wx/sizer.h>
#endif

#include "win_icon.xpm"
#include <wx/dcbuffer.h>
#include <wx/dcps.h>
#include <wx/utils.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <wx/scrolwin.h>
#include <wx/spinctrl.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/event.h>
#include <wx/grid.h>
#include <wx/aboutdlg.h>
#include <wx/gauge.h>
#include <wx/fs_mem.h>
#include <wx/html/htmlwin.h>

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <fstream>

typedef unsigned int uint;
typedef double TYPE_VALEUR_LIEN;
typedef std::string TYPE_VALEUR_SOMMET;

static const double PI = 3.1415926;
static const int angle_par_defaut = 1000;
static const int rayon_sommet = 20;

template<class T>
std::string to_string(const T& t)
{
	std::ostringstream oss;
	oss << t;
	return oss.str();
}

template<class T>
double to_double(const T& t)
{
	std::istringstream iss(t);
	double val;
	iss >> val;
	return val;
}

//----------------------------------------------------------------

struct Rotation
{
	static double degree_to_radian(const double degree)
	{
		return (360 - degree)*PI / 180;
	}

	/*
		x' = x*cos(θ) - y*sin(θ)
		y' = x*sin(θ) + y*cos(θ)
	*/
	static wxPoint rotation_point(const wxPoint& center, const wxPoint& xy, double degree_de_rotation)
	{
		return wxPoint(cos(degree_to_radian(degree_de_rotation))*(xy.x - center.x)
			- sin(degree_to_radian(degree_de_rotation))*(xy.y - center.y) + center.x,
			sin(degree_to_radian(degree_de_rotation))*(xy.x - center.x)
			+ cos(degree_to_radian(degree_de_rotation))*(xy.y - center.y) + center.y
			);
	}
};

//----------------------------------------------------------------

// IDs des notebooks
enum
{
	ID_NB_DESSIN	= 10, // pour le dessin
	ID_NB_SLL		= 11, // pour la liste des sommet et arete/arc (sommet-lien-list)
	ID_NB_SL		= 12 // table des successeur (successeur-list)
};

//----------------------------------------------------------------

// IDs du graphe
enum
{
	ID_ARETE		= 100,
	ID_SUP_ARETE	= 101,
	ID_ARC			= 102,
	ID_SUP_ARC		= 103,
	ID_SOMMET		= 104,
	ID_SUP_SOMMET	= 105,
	ID_MOD_SOMMET   = 106,
	ID_MA			= 107,
	ID_MI			= 108,
	ID_MV			= 109,
	ID_MOD_LIEN     = 110
};

//----------------------------------------------------------------

// IDs pour nouveau
enum 
{
	ID_CHOIX = 200,
	ID_LARGEUR = 201,
	ID_HAUTEUR = 202,
	ID_TYPE_GRAPHE = 203,
	ID_REINITIALISER = 204,
	ID_VALIDER = 205,
	ID_ANNULER = 206
};

//----------------------------------------------------------------

// ID generer l'algorithme

enum { ID_GENERER };

//----------------------------------------------------------------

// ID pour le suivi des algorithmes a matrices 
enum
{
	ID_PRECEDENT = 1,
	ID_SUIVANT   = 2,
	ID_TERMINER  = 3
};

#endif // GLOBAL GUARD