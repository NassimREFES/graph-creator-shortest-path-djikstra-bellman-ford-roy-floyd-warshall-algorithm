#ifndef MAINFRAME_GUARD
#define MAINFRAME_GUARD

#include "global.h"

#ifndef DIJKSTRA_GUARD
	#include "dijkstra.h"
	#include "dijkstra.cpp"
#endif

#ifndef BELLMANFORD_GUARD
	#include "bellmanford.h"
	#include "bellmanford.cpp"
#endif

#ifndef ROY_FLOYD_WARSHALL_GUARD
	#include "roy_floyd_warshall.h"
	#include "roy_floyd_warshall.cpp"
#endif

// ---------------------------------------------------------
// ---------------  Crée un Contexte -----------------------
// ---------------------------------------------------------

class Nouveau : public wxDialog
{
public:
	Nouveau();

	// remetre les parametres par defaut
	void OnReinitialiser(wxCommandEvent&);

	// confirmer la modification
	void OnValider(wxCommandEvent&);

	// sortir du dialog
	void OnAnnuler(wxCommandEvent&);

	// choix du type de graphe
	void OnChoix(wxCommandEvent&);

	// taille du contexte de peripherique
	wxSize taille() const;

	// graphe choisi est orienté
	bool graphe_oriente() const;

	// graphe choisi est non orienté
	bool graphe_non_oriente() const;

	// valider les parametres choisi
	bool valider() const;

private:
	wxButton* m_reinitialiser;
	wxButton* m_valider;
	wxButton* m_annuler;
	bool m_valider_info;

	wxChoice* m_choix;
	wxSpinCtrl* m_largeur;
	wxSpinCtrl* m_hauteur;

	wxRadioBox* m_type_graphe;

	wxSize m_taille;
	bool m_oriente;

private:
	DECLARE_EVENT_TABLE()
};

// ---------------------------------------------------------
// ---------------  Graphe dessin --------------------------
// ---------------------------------------------------------

class Dessin_Graphe;

// table de dessin
struct nb_dessin : wxNotebook
{
	nb_dessin(wxWindow* parent, wxWindowID id);

	Dessin_Graphe* graphe;
};

// ---------------------------------------------------------
// ---------------  Table des successeur -------------------
// ---------------------------------------------------------

struct nb_table_succ : wxNotebook
{
	nb_table_succ(wxWindow* parent, wxWindowID id);
	nb_table_succ(wxWindow* parent, wxWindowID id, 
		const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls);

	// modifier la table des successeurs
	void set_table(const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls);

	wxListView* list;
private :
	// preparé la table des successeurs
	void init_table();
};

// ---------------------------------------------------------
// ---------------  Table des sommets-liens ----------------------
// ---------------------------------------------------------

struct nb_table_sl : wxNotebook
{
	nb_table_sl(wxWindow* parent, wxWindowID id, bool oriente);
	nb_table_sl(wxWindow* parent, wxWindowID id, 
		const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls,
		const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_arc& la, bool oriente);

	// modifier la table des sommets et liens(arc/arete)
	void set_table(const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls,
		const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_arc& la);

	/* 
		modifier les noms des position des sommets d'un lien selon le type du graphe
		oriente : 
			- sommet initial
			- sommet final
		non oriente :
			- premier sommet
			- deuxieme sommet
	*/
	void set_name_table();

	// liste des sommets
	wxListView* list;

	// liste des liens(arc/arete)
	wxListView* list1;

	// type du graphe
	bool m_oriente;
private:
	// preparé la table des sommets et liens
	void init_table();
};


// ---------------------------------------------------------
// ---------------  Fenetre principale  --------------------
// ---------------------------------------------------------

class MainFrame : public wxFrame
{
public :
	// taille de la table de dessin
	wxSize taille_contexte_peripherique;

	// type du graphe
	bool type_graphe_oriente;

	// contexte de peripherique on bitmap 
	wxBitmap bitmapDC;

	// nom du bitmapDC a enregistrer
	wxString namefile;

public:
	MainFrame();

	// Demarrer
	void OnNouveau(wxCommandEvent&);

	/*
		- enregistrement de l'image
		- enregistrement du projet

			- format utilisé :
				tdc taille_context.x taille_context.y
				tg 1 (pour oriente) ou 0 (pour non oriente)
				Sommet { (s1 sp1.x sp1.y) (s2 sp2.x sp2.y) ... }
				Arc { (a1.poid a1.si a1.sf) ( a2.poid a2.si s2.sf ) ... }

				***
					pour un graphe non orienté en ajoute selement un arc
					et non 2 arc inverse dans Arc { ... }
				***
	*/
	void OnEnregistrer(wxCommandEvent&);

	/*
		- ouverture du projet precedement enregistrer
		- ouvrir que les fichier a extension ( .graphe )
	*/
	void OnOuvrir(wxCommandEvent&);
	void OnQuitter(wxCommandEvent&);

	/*
		aide l'utilisation a comprendre le 
		fonctionnement de l'application
	*/
	void OnAide(wxCommandEvent&);
	void OnApropos(wxCommandEvent&);

	// Modifier
	void OnSommet(wxCommandEvent&);
	bool OnSommetClicked() const;
	void OnSupSommet(wxCommandEvent&);
	bool OnSupSommetClicked() const;
	void OnModSommet(wxCommandEvent&);
	bool OnModSommetClicked() const;

	void OnArete(wxCommandEvent&);
	bool OnAreteClicked() const;
	void OnSupArete(wxCommandEvent&);
	bool OnSupAreteClicked() const;
	void OnModLien(wxCommandEvent&);
	bool OnModLienClicked() const;

	// Gere les algorithmes
	void OnGenerer(wxCommandEvent&);
	void OnMatriceAdjacence(wxCommandEvent&);
	void OnMatriceIncidence(wxCommandEvent&);
	void OnMatriceValuation(wxCommandEvent&);

	// effacer tout se qu'il ya sur le DC
	void OnEffacer(wxCommandEvent&);

	void OnPaint(wxPaintEvent&);

	// la pair de sommet selectionnée
	std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> > pair_sommet;

	// modifier la table de successeur
	void set_table_successeur(const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls);

	// le chemin de l'algorithme
	std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> > parcour_algorithme(Graphe::Sommet<TYPE_VALEUR_SOMMET>) const;

	// sommet de destination ( pour algorithme )
	Graphe::Sommet< TYPE_VALEUR_SOMMET > get_destinataire() const;

public :
	// algorithme choisi
	Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>* m_algorithme;
	Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>* mp_algorithme;
	bool mp_algo;
	// afficher le resultat de l'algorithme
	bool afficher_resultat_algorithme;
	Graphe::Sommet<TYPE_VALEUR_SOMMET> destinataire;

private:
	wxMenuBar* m_menubar;

	wxMenu* m_fichier;
	wxMenuItem* m_nouveau;
	wxMenuItem* m_enregistrer;
	wxMenuItem* m_ouvrir;
	wxMenuItem* m_quiter;
	wxMenu* m_modifier;

	wxMenu* m_aide;
	wxMenuItem* m_apropos;
	wxMenuItem* m_afficher_aide;

	wxToolBar* m_toolbar;

	wxButton* m_matrice_associe;
	wxButton* m_matrice_incidence;
	wxButton* m_matrice_valuation;
	wxButton* m_effacer;

	bool ajoute_sommet;
	bool supprimer_sommet;
	bool modifier_sommet;

	bool ajoute_arete;
	bool supprimer_arete;
	bool modifier_lien;

	bool pour_nouveau;

	wxChoice* m_choix_algo;
	wxTextCtrl* m_source;
	wxTextCtrl* m_dest;
	wxButton* m_generer;

	bool nouveau_avant;

private:
	DECLARE_EVENT_TABLE()
	void init_menubar();
	void init_toolbar();
	bool enregistrement(wxString nf);
	bool ouverture(wxString nf);
	void set_tool(bool t);

public :
// les trois widget principale
	nb_dessin* m_nb;		// pour le dessins
	nb_table_succ* m_nts;	// pour la liste de successeur
	nb_table_sl* m_nt;		// pour la liste des sommets et liens(arc/arete)
};

// ---------------------------------------------------------
// ---------------  Lien a supprimer -----------------------
// ---------------------------------------------------------

class Del_Lien : public wxDialog
	// dialog pour la supression d'un lien
{
public :
	// position du lien dans la liste des lien + le lien
	Del_Lien(const std::vector< std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > >&);

	// choix du lien a supprimer
	void OnChoix(wxCommandEvent& event);

	// valider le choix
	void OnValider(wxCommandEvent& event);

	// ne plus supprimer de lien
	void OnAnnuler(wxCommandEvent& event);

	// avoir le lien choisi
	int mon_choix() const;

	// valider la suppression
	bool valider() const;

private :
	wxChoice* m_choix;
	wxButton* m_annuler;
	wxButton* m_ok;
	int m_lien_choisi;
	bool m_valider;
	DECLARE_EVENT_TABLE()
};


// ---------------------------------------------------------
// ---------------  Lien a modifier ------------------------
// ---------------------------------------------------------

class Mod_Lien : public wxDialog
	// dialog pour la modification du poid d'un lien(arc/arete)
{
public :
	// position du lien dans la liste des lien + le lien
	Mod_Lien(const std::vector< std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > >&);

	// choix du lien
	void OnChoix(wxCommandEvent& event);

	// valider le choix
	void OnValider(wxCommandEvent& event);

	// annuler la modification
	void OnAnnuler(wxCommandEvent& event);

	// nouvelle valeur pour le lien
	void OnValeur(wxSpinDoubleEvent& event);

	// position du lien choisi
	int mon_choix() const;

	// nouvelle valeur du lien
	double ma_valeur() const;

	// valider la modification
	bool valider() const;
private :
	wxChoice* m_choix;
	wxButton* m_annuler;
	wxButton* m_ok;
	wxSpinCtrlDouble* m_mv;
	int m_lien_choisi;
	double m_valeur;
	bool m_valider;
	DECLARE_EVENT_TABLE()
};

// ---------------------------------------------------------
// ---------------  Graphe valué dessin --------------------
// ---------------------------------------------------------

class Dessin_Graphe : public wxScrolledCanvas
{
public:
	Dessin_Graphe(wxNotebook* parent);

	// Demmarer
	void OnPaint(wxPaintEvent&);
	void OnEraseBackground(wxEraseEvent&);
	void PaintBackground(wxDC&);

	// Modifier
	void OnMotion(wxMouseEvent&);
	void OnErase(wxEraseEvent&);
	void OnScroll(wxScrollWinEvent&);

	// avoir le graphe dessiner
	Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>& get_graphe();

	// effacer le graphe 
	void efface_graphe();

	// modifier le type du graphe
	void set_type_graphe(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type);

	// reglage du scrollbar
	void set_scrollbar();

	// position courante du scrollbar
	wxPoint scrollbar_pos() const;

	std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> > list_sommets;
	std::vector< Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > list_arc;

private:
	DECLARE_EVENT_TABLE()
	MainFrame* m_parent;
	Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> graphe;
	wxPoint m_ajoute_a_sourie;

	bool sommet_existe(TYPE_VALEUR_SOMMET s);
	std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator sommet_existe_en_pos(wxPoint p);
	std::vector< Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >::iterator
		lien_existe(const Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>&);

	Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> graphe_resultat_algorithme;
	void dessiner_graphe_resultat_algorithme(wxDC& dc, wxPen lien, wxPen sommet, bool afficher_poid);

	std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator sd; // sommet a deplacer
	bool ok;

private:
// aide a <Modifier>
	void ajoute_sommet(wxDC&, wxMouseEvent&);
	void supprimer_sommet(wxMouseEvent&);
	void modifier_sommet(wxMouseEvent&);
	void deplacer_sommet(wxMouseEvent&);
	void ajoute_arete(wxDC&, wxMouseEvent&);
	void supprimer_arete(wxMouseEvent&);
	void ajoute_arc(wxDC&, wxMouseEvent&);
	void supprimer_arc(wxMouseEvent&);
	void modifier_lien(wxMouseEvent&);
};

// ---------------------------------------------------------
// ---------------  Tracé d'un algorithme  -----------------
// ---------------------------------------------------------

struct Trace : wxFrame
	/* 
		Tableau de suivi des algorithmes :
			- Dijkstra
			- Bellman-Ford
	*/
{
	Trace(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> graphe, 
		std::vector< std::vector<TYPE_VALEUR_LIEN> >,
		Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type);
};

struct Trace_Matrice : wxFrame
	/*
		Tableau de suivi des algorithmes a base de matrice :
			- Roy-Floyd-Warshall
	*/
{
	Trace_Matrice(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> graphe,
		std::vector< std::vector< std::vector<TYPE_VALEUR_LIEN> > >,
		Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type);

	// Matrice de suivi precedente
	void OnPrecedent(wxCommandEvent&);

	// matrice de suivi suivante
	void OnSuivant(wxCommandEvent&);

	// fin de suivi ( resultat final )
	void OnTerminer(wxCommandEvent&);

private :
	wxGrid* m_grid;
	wxStaticText* m_iteration;
	int m_iteration_count;
	int m_dernier_iteration;
	wxButton* m_precedent;
	wxButton* m_suivant;
	wxButton* m_terminer;
	std::vector< std::vector< std::vector<TYPE_VALEUR_LIEN> > > m_v;

private :
	void set();
	DECLARE_EVENT_TABLE()
};

#endif