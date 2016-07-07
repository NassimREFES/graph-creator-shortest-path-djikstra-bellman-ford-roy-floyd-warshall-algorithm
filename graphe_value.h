#ifndef GRAPHE_VALUE_GUARD
#define GRAPHE_VALUE_GUARD

#ifndef ARC_GUARD
	#include "arc.h"
	#include "arc.cpp"
#endif

using Graphe::Sommet;
using Graphe::Arete;
using Graphe::Arc;

// ---------------------------------------------------------
// ---------------------  Graphe valué  --------------------
// ---------------------------------------------------------

template<class TA, class TS> class Graphe_value
	/*
	TA : type Arc
	TS : type Sommet
	*/
{
public:
	typedef typename std::vector< std::vector<Sommet<TS> > > List_successeur;
	typedef typename std::vector< Graphe::Arc<TA, TS> > List_arc;

	// les deux type qu'un graphe peux avoir
	enum Type { ORIENTE = 1, NON_ORIENTE };

	Graphe_value(Type type);
	~Graphe_value();

	// ajoute un sommet
	void add_sommet(Sommet<TS> n_sommet);

	// supprimer un sommet
	void del_sommet(Sommet<TS> s);

	// modifier le nom et/ou position
	void mod_sommet(Sommet<TS> s, Sommet<TS> n);

	// ajoute un arc
	void add_arc(Graphe::Arc<TA, TS> n_arc);

	// supprimer un arc
	void del_arc(Graphe::Arc<TA, TS> a);

	// ajoute une arete
	void add_arete(Arete<TA, TS> n_arete);

	// supprimer une arete
	void del_arete(Arete<TA, TS> a);

	// modifier la valeur d'un lien
	void mod_lien(Graphe::Arc<TA, TS> a, TA np);

	/* 
		la listes des successeur pour i ∈ [0, nombre_sommet()[ et j = 0 
		successeur[i][j] = represente la liste des sommets
						   selon l'ordre de l'entrée
		pour j ∈ [1, successeur[i].size()[ = represente les successeurs
													de successeur[i][0]
	*/
	const List_successeur& list_successeur() const;

	/* 
		la listes des arcs pour i ∈ [0, nombre_arc()[
		oriente :
			arcs[i] = represente un arc
		non oriente :
			arcs[i] et arcs[i+1] = represente la pair d'arc 
								   inverse pour une arete
	*/
	const List_arc& list_arcs() const;

	// le nombre de sommet que le graphe possede
	uint nombre_sommet() const;

	// le nombre d'arc que le graphe possede
	uint nombre_arc() const;

	// le nombre d'arete que le graphe possede
	uint nombre_arete() const;

	// avoir la position du sommet dans la liste de sommets
	uint position_sommet(Sommet<TS>) const;

	// modifier le type du graphe
	void set_type(Type);

	// graphe orienté
	bool oriente() const;

	// graphe non orienté
	bool non_oriente() const;

	/*
		dessiner le graphe sous forme graphique
	*/
	void dessiner(wxDC& dc, wxPen lien, wxPen sommet, bool afficher_poid);

	/*
		0 : pas de lien entre la pair de sommet
		n : le nombre de lien entre pair de sommet
	*/
	std::vector< std::vector<int> > matrice_adjacence() const;

	/*
			-2 : (boucle)
		oriente :
			-1 : si sommet est l'extremité initial le l'arc
			1 : si sommet est l'extremité final de l'arc
			0 : sinon
		non oriente :
			1 : si sommet est une extremité d'une arete
			0 : non
	*/
	std::vector< std::vector<int> > matrice_incidence() const;

	/*
		representation du graphe sous forme de matrice sommet-sommet
		valeur du lien : si ya un lien entre la pair de sommet
		INF            : si ya pas de lien entre la pair de sommet
		0              : si la pair de sommet sont les memes et ya 
		                 pas de lien pour cette pair

	*/
	std::vector< std::vector<TA> > matrice_valuation() const;

	/* 
		mettre les liens par ordre croissant selon leur poid
		dans la liste de liens
	*/
	// void aranger();

	Graphe_value& operator=(const Graphe_value<TA, TS>&);
	Graphe_value(const Graphe_value&);
private:
	List_successeur m_ls;
	List_arc        m_arc;
	bool m_oriente;
};

#endif // GRAPHE_VALUE_GUARD