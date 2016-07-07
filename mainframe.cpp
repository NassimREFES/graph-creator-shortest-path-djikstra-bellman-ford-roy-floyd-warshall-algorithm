#include "mainframe.h"

//------------------------------------------------------------------

BEGIN_EVENT_TABLE(Nouveau, wxDialog)
	EVT_CHOICE(ID_CHOIX, Nouveau::OnChoix)
	EVT_BUTTON(ID_REINITIALISER, Nouveau::OnReinitialiser)
	EVT_BUTTON(ID_VALIDER, Nouveau::OnValider)
	EVT_BUTTON(ID_ANNULER, Nouveau::OnAnnuler)
END_EVENT_TABLE()

//------------------------------------------------------------------

Nouveau::Nouveau()
: m_taille(wxSystemSettings::GetMetric(wxSYS_SCREEN_X),
wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)), m_oriente(false),
wxDialog(NULL, wxID_ANY, wxT("Crée un nouveau graphe"), wxDefaultPosition,
wxSize(400, 305), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
	wxBoxSizer* vbox_global = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox_modele = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox_button = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox_largeur = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox_hauteur = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* modele = new wxStaticText(this, wxID_ANY, wxT("Modele :"));
	wxString table_choix[] = { "Taille de l'ecran",
		"320 x 240",
		"640 x 480",
		"800 x 600",
		"1024 x 768",
		"1600 x 1200"
	};
	m_choix = new wxChoice(this, ID_CHOIX, wxDefaultPosition, wxDefaultSize, 6, table_choix);
	m_choix->SetSelection(0);
	hbox_modele->Add(modele, 0, wxEXPAND | wxALL, 5);
	hbox_modele->Add(m_choix, 1, wxEXPAND | wxALL, 5);

	wxStaticText* taille = new wxStaticText(this, wxID_ANY, wxT("Taille de l'image :"));
	wxStaticText* largeur = new wxStaticText(this, wxID_ANY, wxT("Largeur : "));
	wxStaticText* hauteur = new wxStaticText(this, wxID_ANY, wxT("Hauteur :"));
	m_largeur = new wxSpinCtrl(this, ID_LARGEUR, to_string(wxSystemSettings::GetMetric(wxSYS_SCREEN_X)));
	m_largeur->SetMax(2000);
	m_hauteur = new wxSpinCtrl(this, ID_HAUTEUR, to_string(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)));
	m_hauteur->SetMax(2000);

	wxString type[] { "Oriente",
		"Non Oriente"
	};
	m_type_graphe = new wxRadioBox(this, ID_TYPE_GRAPHE, wxT("Type De Graphe"),
		wxDefaultPosition, wxDefaultSize, 2, type);
	m_type_graphe->SetSelection(0);

	hbox_largeur->Add(largeur, 0, wxLEFT | wxALIGN_CENTER, 80);
	hbox_largeur->Add(m_largeur, 0, wxALL | wxALIGN_CENTER, 5);
	hbox_hauteur->Add(hauteur, 0, wxLEFT | wxALIGN_CENTER, 80);
	hbox_hauteur->Add(m_hauteur, 0, wxALL | wxALIGN_CENTER, 5);

	m_reinitialiser = new wxButton(this, ID_REINITIALISER, wxT("Reinitialiser"));
	m_valider = new wxButton(this, ID_VALIDER, wxT("Valider"));
	m_annuler = new wxButton(this, ID_ANNULER, wxT("Annuler"));

	hbox_button->Add(m_reinitialiser, 1, wxEXPAND | wxALL, 10);
	hbox_button->Add(m_valider, 1, wxEXPAND | wxALL, 10);
	hbox_button->Add(m_annuler, 1, wxEXPAND | wxALL, 10);

	vbox_global->Add(hbox_modele, 1, wxEXPAND | wxALL, 5);
	vbox_global->Add(taille, 0, wxEXPAND | wxALL, 10);
	vbox_global->Add(hbox_largeur, 1, wxEXPAND | wxLEFT | wxALIGN_RIGHT, 5);
	vbox_global->Add(hbox_hauteur, 1, wxEXPAND | wxLEFT | wxALIGN_RIGHT, 5);
	vbox_global->Add(m_type_graphe, 0, wxALL | wxALIGN_LEFT, 10);
	vbox_global->Add(hbox_button, 1, wxEXPAND | wxALL | wxALIGN_CENTER, 5);

	this->SetSizer(vbox_global);
	this->Center();
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
}

//------------------------------------------------------------------

void Nouveau::OnReinitialiser(wxCommandEvent& event)
{
	m_choix->SetSelection(0);
	m_largeur->SetValue(wxSystemSettings::GetMetric(wxSYS_SCREEN_X));
	m_hauteur->SetValue(wxSystemSettings::GetMetric(wxSYS_SCREEN_Y));
	m_type_graphe->SetSelection(0);
}

//------------------------------------------------------------------

void Nouveau::OnValider(wxCommandEvent& event)
{
	m_taille = wxSize(m_largeur->GetValue(), m_hauteur->GetValue());
	m_oriente = m_type_graphe->GetSelection() == 0 ? true : false;
	m_valider_info = true;
	wxString x;
	x << m_taille.x << ", " << m_taille.y << " | " << (m_oriente ? "oriente" : "non oriente");
	wxMessageBox(x, wxT("Message"));
	EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

//------------------------------------------------------------------

void Nouveau::OnAnnuler(wxCommandEvent& event)
{
	m_valider_info = false;
	EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

//------------------------------------------------------------------

void Nouveau::OnChoix(wxCommandEvent& event)
{
	wxSize s[] = {
		wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X),
		wxSystemSettings::GetMetric(wxSYS_SCREEN_Y)),
		wxSize(320, 240),
		wxSize(640, 480),
		wxSize(800, 600),
		wxSize(1024, 768),
		wxSize(1600, 1200)
	};
	m_largeur->SetValue(s[m_choix->GetSelection()].x);
	m_hauteur->SetValue(s[m_choix->GetSelection()].y);
}

//------------------------------------------------------------------

inline wxSize Nouveau::taille() const
{
	return m_taille;
}

//------------------------------------------------------------------

inline bool Nouveau::graphe_oriente() const
{
	return m_oriente;
}

//------------------------------------------------------------------

inline bool Nouveau::graphe_non_oriente() const
{
	return !m_oriente;
}

//------------------------------------------------------------------

inline bool Nouveau::valider() const
{
	return m_valider_info;
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

nb_dessin::nb_dessin(wxWindow* parent, wxWindowID id)
	: wxNotebook(parent, id)
{
	graphe = new Dessin_Graphe(this);
	this->AddPage(graphe, "Graphe Value");
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

nb_table_succ::nb_table_succ(wxWindow* parent, wxWindowID id)
	: wxNotebook(parent, id) 
{
	list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	init_table();
	set_table(((MainFrame*)parent)->m_nb->graphe->get_graphe().list_successeur());
	this->AddPage(list, "List Successeur");
}

//------------------------------------------------------------------

nb_table_succ::nb_table_succ(wxWindow* parent, wxWindowID id, 
	const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls)
	: wxNotebook(parent, id)
{
	list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	init_table();
	set_table(ls);
	this->AddPage(list, "List Successeur");
}

void nb_table_succ::init_table()
{
	wxListItem nom_sommet;
	nom_sommet.SetId(0);
	nom_sommet.SetText(wxT("Sommet"));
	//nom_sommet.SetWidth(150);
	list->InsertColumn(0, nom_sommet);

	wxListItem succ;
	succ.SetId(1);
	succ.SetText(wxT("Successeur(s)"));
	//succ.SetWidth(150);
	list->InsertColumn(1, succ);
}

//------------------------------------------------------------------

void nb_table_succ::set_table(const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls)
{
	list->DeleteAllItems();

	for (uint i = 0; i < ls.size(); ++i) {
		list->InsertItem(i, wxT(""));
		list->SetItem(i, 0, to_string(ls[i][0].get()));

		wxString x;
		if (ls[i].size() == 1)
			x << "<NULL>";
		else
			for (uint j = 1; j < ls[i].size(); ++j) {
				x << to_string(ls[i][j]);
				if (j < ls[i].size() - 1)
					x << ", ";
			}
		list->SetItem(i, 1, x);
	}
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

nb_table_sl::nb_table_sl(wxWindow* parent, wxWindowID id, bool oriente)
	: wxNotebook(parent, id), m_oriente(oriente)
{
	list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	list1 = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	init_table();
	set_table(((MainFrame*)parent)->m_nb->graphe->get_graphe().list_successeur(),
		((MainFrame*)parent)->m_nb->graphe->get_graphe().list_arcs());
	this->AddPage(list, "List Sommets");
	this->AddPage(list1, "List Arete/Arc");
}

//------------------------------------------------------------------

nb_table_sl::nb_table_sl(wxWindow* parent, wxWindowID id,
	const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls,
	const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_arc& la, bool oriente)
	: wxNotebook(parent, id), m_oriente(oriente)
{
	list = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	list1 = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
	init_table();
	set_table(ls, la);
	this->AddPage(list, "List Sommets");
	this->AddPage(list1, "List Arete/Arc");
}

void nb_table_sl::set_name_table()
{
	wxListItem init_sommet;
	wxListItem fin_sommet;

	if (m_oriente) {
		init_sommet.SetText(wxT("Sommet Initial"));
		fin_sommet.SetText(wxT("Sommet Final"));
	}
	else {
		init_sommet.SetText(wxT("Premier Sommet"));
		fin_sommet.SetText(wxT("Deuxieme Sommet"));
	}

	list1->SetColumn(1, init_sommet);
	list1->SetColumn(2, fin_sommet);
}

void nb_table_sl::init_table()
{
	wxListItem indice_sommet;
	indice_sommet.SetId(0);
	indice_sommet.SetText(wxT("Indice"));
	//indice_sommet.SetWidth(150);
	list->InsertColumn(0, indice_sommet);

	wxListItem nom_sommet;
	nom_sommet.SetId(1);
	nom_sommet.SetText(wxT("Nom"));
	//nom_sommet.SetWidth(150);
	list->InsertColumn(1, nom_sommet);

	wxListItem position;
	position.SetId(2);
	position.SetText("Position");
	//position.SetWidth(150);
	list->InsertColumn(2, position);

	wxListItem init_sommet;
	wxListItem fin_sommet;
	wxListItem indice_lien;

	indice_lien.SetText(wxT("Nom"));

	if (m_oriente) {
		init_sommet.SetText(wxT("Sommet Initial"));
		fin_sommet.SetText(wxT("Sommet Final"));
	}
	else {
		init_sommet.SetText(wxT("Premier Sommet"));
		fin_sommet.SetText(wxT("Deuxieme Sommet"));
	}

	init_sommet.SetId(0);
	//init_sommet.SetWidth(150);
	list1->InsertColumn(0, indice_lien);

	init_sommet.SetId(1);
	//init_sommet.SetWidth(150);
	list1->InsertColumn(1, init_sommet);

	fin_sommet.SetId(2);
	//fin_sommet.SetWidth(150);
	list1->InsertColumn(2, fin_sommet);

	wxListItem poid;
	poid.SetId(3);
	poid.SetText("Poid");
	//poid.SetWidth(150);
	list1->InsertColumn(3, poid);
}

//------------------------------------------------------------------

void nb_table_sl::set_table(const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_successeur& ls,
	const Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::List_arc& la)
{
	list->DeleteAllItems();

	for (uint i = 0; i < ls.size(); ++i) {
		list->InsertItem(i, wxT(""));
		list->SetItem(i, 0, to_string(i));
		list->SetItem(i, 1, to_string(ls[i][0].get()));
		wxString x;
		x << "x : " << ls[i][0].position().x << ", y :" << ls[i][0].position().y;
		list->SetItem(i, 2, x);
	}

	list1->DeleteAllItems();

	int add = m_oriente ? 1 : 2;
	
	for (uint i = 0, j = 0; i < la.size(); i+=add, ++j) {
		list1->InsertItem(i, wxT(""));
		list1->SetItem(j, 0, std::string("u")+to_string(j));
		list1->SetItem(j, 1, to_string(la[i].sommet_initial()));
		list1->SetItem(j, 2, to_string(la[i].sommet_final()));
		list1->SetItem(j, 3, to_string(la[i].poid()));
	}
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_NEW, MainFrame::OnNouveau)
	EVT_MENU(wxID_SAVE, MainFrame::OnEnregistrer)
	EVT_MENU(wxID_OPEN, MainFrame::OnOuvrir)
	EVT_MENU(wxID_EXIT, MainFrame::OnQuitter)
	EVT_MENU(wxID_HELP, MainFrame::OnAide)
	EVT_MENU(wxID_ABOUT, MainFrame::OnApropos)
	EVT_MENU(ID_SOMMET, MainFrame::OnSommet)
	EVT_MENU(ID_SUP_SOMMET, MainFrame::OnSupSommet)
	EVT_MENU(ID_MOD_SOMMET, MainFrame::OnModSommet)
	EVT_MENU(ID_ARETE, MainFrame::OnArete)
	EVT_MENU(ID_SUP_ARETE, MainFrame::OnSupArete)
	EVT_MENU(ID_ARC, MainFrame::OnArete)
	EVT_MENU(ID_SUP_ARC, MainFrame::OnSupArete)
	EVT_MENU(ID_MOD_LIEN, MainFrame::OnModLien)
	EVT_BUTTON(ID_GENERER, MainFrame::OnGenerer)
	EVT_BUTTON(ID_MA, MainFrame::OnMatriceAdjacence)
	EVT_BUTTON(ID_MI, MainFrame::OnMatriceIncidence)
	EVT_BUTTON(ID_MV, MainFrame::OnMatriceValuation)
	EVT_BUTTON(wxID_CLEAR, MainFrame::OnEffacer)
	EVT_PAINT(MainFrame::OnPaint)
END_EVENT_TABLE()

//------------------------------------------------------------------

MainFrame::MainFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Graphe"), wxDefaultPosition,
	wxSize(wxSystemSettings::GetMetric(wxSYS_SCREEN_X), wxSystemSettings::GetMetric(wxSYS_SCREEN_Y) - 45), 
		(wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE)),
	ajoute_sommet(false), supprimer_sommet(false),
	ajoute_arete(false), supprimer_arete(false),
	pour_nouveau(false), m_algorithme(NULL),
	afficher_resultat_algorithme(false),
	modifier_sommet(false),
	mp_algo(false), mp_algorithme(NULL)
{
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxBMPHandler);
	init_menubar();
	init_toolbar();
	Centre();
	SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
	CreateStatusBar(3);

	wxBoxSizer* global_bs = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* bs = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* vbs = new wxBoxSizer(wxVERTICAL);
	wxGridSizer* gs = new wxGridSizer(2, 4, 0, 0);

	m_nb = new nb_dessin(this, ID_NB_DESSIN);
	m_nts = new nb_table_succ(this, ID_NB_SL, m_nb->graphe->get_graphe().list_successeur());
	m_nt = new nb_table_sl(this, ID_NB_SLL, m_nb->graphe->get_graphe().list_successeur(),
		m_nb->graphe->get_graphe().list_arcs(), m_nb->graphe->get_graphe().oriente());

	wxString s[] = { "Dijkstra", "BellmanFord", "Roy-Floyd-Warshall" };
	wxStaticText* algo = new wxStaticText(this, wxID_ANY, wxT("Algorithme"));
	algo->SetBackgroundColour(wxColor(174, 204, 203));
	wxStaticText* source = new wxStaticText(this, wxID_ANY, wxT("Depart"));
	source->SetBackgroundColour(wxColor(174, 204, 203));
	wxStaticText* dest = new wxStaticText(this, wxID_ANY, wxT("Arrivée"));
	dest->SetBackgroundColour(wxColor(174, 204, 203));
	m_choix_algo = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 3, s);
	m_source = new wxTextCtrl(this, wxID_ANY, wxT(""));
	m_dest = new wxTextCtrl(this, wxID_ANY, wxT(""));
	m_generer = new wxButton(this, ID_GENERER, wxT("Generer"));

	gs->Add(algo, 1);
	gs->Add(source, 1);
	gs->Add(dest, 1);
	gs->Add(new wxStaticText(this, wxID_ANY, wxT("")), 0);
	gs->Add(m_choix_algo, 1);
	gs->Add(m_source, 1);
	gs->Add(m_dest, 1);
	gs->Add(m_generer, 1);

	vbs->Add(m_nt, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);
	vbs->Add(m_nts, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);
	bs->Add(m_nb, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);
	bs->Add(gs, 0, wxEXPAND | wxALL, 5);
	global_bs->Add(bs, 2, wxEXPAND | wxTOP, 50);
	global_bs->Add(vbs, 0, wxEXPAND | wxTOP, 50);

	this->SetSizer(global_bs);

	m_toolbar->EnableTool(ID_SOMMET, false);
	m_toolbar->EnableTool(ID_SUP_SOMMET, false);
	m_toolbar->EnableTool(ID_MOD_SOMMET, false);
	m_toolbar->EnableTool(ID_ARETE, false);
	m_toolbar->EnableTool(ID_SUP_ARETE, false);
	m_toolbar->EnableTool(ID_ARC, false);
	m_toolbar->EnableTool(ID_SUP_ARC, false);
	m_toolbar->EnableTool(ID_MOD_LIEN, false);
	m_toolbar->EnableTool(wxID_SAVE, false);
//	m_toolbar->EnableTool(wxID_OPEN, false);
	
	m_menubar->Enable(ID_SOMMET, false);
	m_menubar->Enable(ID_SUP_SOMMET, false);
	m_menubar->Enable(ID_MOD_SOMMET, false);
	m_menubar->Enable(ID_ARETE, false);
	m_menubar->Enable(ID_SUP_ARETE, false);
	m_menubar->Enable(ID_ARC, false);
	m_menubar->Enable(ID_SUP_ARC, false);
	m_menubar->Enable(ID_MOD_LIEN, false);
	m_menubar->Enable(wxID_SAVE, false);
//	m_menubar->Enable(wxID_OPEN, false);

	m_nb->Freeze();
	m_nts->Freeze();
	m_nt->Freeze();

	this->SetMinSize(wxSize(1000, 500));
	this->SetBackgroundColour(*wxLIGHT_GREY);
}

//------------------------------------------------------------------

void MainFrame::OnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);
	PrepareDC(dc);
	wxBitmap bmp("image/back.jpg", wxBITMAP_TYPE_JPEG);
	dc.DrawBitmap(bmp, wxPoint(0,0));
}


//-----------------------------------------------------------------

void MainFrame::init_menubar()
{
	m_menubar = new wxMenuBar;

	m_fichier = new wxMenu;
	m_nouveau = new wxMenuItem(m_fichier, wxID_NEW, wxT("&Nouveau\tCtrl+N"));
	m_enregistrer = new wxMenuItem(m_fichier, wxID_SAVE, wxT("&Enregistrer\tCtrl+S"));
	m_ouvrir = new wxMenuItem(m_fichier, wxID_OPEN, wxT("&Ouvrir...\tCtrl+P"));
	m_quiter = new wxMenuItem(m_fichier, wxID_EXIT, wxT("&Quitter\tCtrl+Q"));
	m_fichier->Append(m_nouveau);
	m_fichier->Append(m_ouvrir);
	m_fichier->AppendSeparator();
	m_fichier->Append(m_enregistrer);
	m_fichier->AppendSeparator();
	m_fichier->Append(m_quiter);

	m_modifier = new wxMenu;
	m_modifier->Append(ID_SOMMET, wxT("Ajouter Sommet\tCtrl+O"));
	m_modifier->Append(ID_ARETE, wxT("Ajouter Arete\tCtrl+I"));
	m_modifier->Append(ID_ARC, wxT("Ajouter Arc\tCtrl+L"));
	m_modifier->Append(ID_SUP_SOMMET, wxT("Supprimer Sommet\tAlt+O"));
	m_modifier->Append(ID_SUP_ARETE, wxT("Supprimer Arete\tAlt+I"));
	m_modifier->Append(ID_SUP_ARC, wxT("Supprimer Arc\tAlt+L"));
	m_modifier->Append(ID_MOD_SOMMET, wxT("Modifier Sommet\tCtrl+M"));
	m_modifier->Append(ID_MOD_LIEN, wxT("Modifier Arc/Arete\tCtrl+P"));

	m_aide = new wxMenu;
	m_afficher_aide = new wxMenuItem(m_aide, wxID_HELP, wxT("&Afficher l'aide\tF1"));
	m_apropos = new wxMenuItem(m_aide, wxID_ABOUT, wxT("A Propos..."));
	m_aide->Append(m_afficher_aide);
	m_aide->Append(m_apropos);

	m_menubar->Append(m_fichier, wxT("&Fichier"));
	m_menubar->Append(m_modifier, wxT("&Modifier"));
	m_menubar->Append(m_aide, wxT("&Aide"));
	this->SetMenuBar(m_menubar);
}

//------------------------------------------------------------------

void MainFrame::init_toolbar()
{
	m_toolbar = new wxToolBar(this, wxID_ANY);

	wxBitmap nouveau(wxT("image/nouveau.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap enregistrer(wxT("image/enregistrer.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap ouvrir(wxT("image/ouvrir.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap quitter(wxT("image/quitter.bmp"), wxBITMAP_TYPE_BMP);

	wxBitmap sommet(wxT("image/sommet.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap sup_sommet(wxT("image/sup_sommet.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap mod_sommet(wxT("image/mod_sommet.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap arete(wxT("image/arete.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap sup_arete(wxT("image/sup_arete.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap arc(wxT("image/arc.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap sup_arc(wxT("image/sup_arc.bmp"), wxBITMAP_TYPE_BMP);
	wxBitmap mod_lien(wxT("image/mod_lien.bmp"), wxBITMAP_TYPE_BMP);

	m_toolbar->AddTool(wxID_NEW, wxT("nouveau"), nouveau, wxT("Nouvelle page"));
	m_toolbar->AddTool(wxID_OPEN, wxT("ouvrir"), ouvrir, wxT("Ouvrir..."));
	m_toolbar->AddTool(wxID_SAVE, wxT("enregistrer"), enregistrer, wxT("Enregistrer"));
	m_toolbar->AddTool(wxID_EXIT, wxT("quitter"), quitter, wxT("Quitter l'application"));
	m_toolbar->AddSeparator();
	m_toolbar->AddSeparator();
	m_toolbar->AddTool(ID_SOMMET, wxT("sommet"), sommet, wxT("Ajouter un sommet"));
	m_toolbar->AddTool(ID_SUP_SOMMET, wxT("sup_sommet"), sup_sommet, wxT("Supprime un sommet"));
	m_toolbar->AddTool(ID_MOD_SOMMET, wxT("mod_sommet"), mod_sommet, wxT("Modifier un sommet"));
	m_toolbar->AddTool(ID_ARETE, wxT("arete"), arete, wxT("Ajouter une arete"));
	m_toolbar->AddTool(ID_SUP_ARETE, wxT("sup_arete"), sup_arete, wxT("Supprime une arete"));
	m_toolbar->AddTool(ID_ARC, wxT("arc"), arc, wxT("Ajouter un arc"));
	m_toolbar->AddTool(ID_SUP_ARC, wxT("sup_arc"), sup_arc, wxT("Supprime un arc"));
	m_toolbar->AddTool(ID_MOD_LIEN, wxT("mod_lien"), mod_lien, wxT("Modifier Arc/Arete"));
	m_effacer = new wxButton(m_toolbar, wxID_CLEAR, wxT("Effacer Tout"));
	m_effacer->SetToolTip(new wxToolTip(wxT("vider la page de dessin")));
	m_toolbar->AddControl(m_effacer);
	m_toolbar->AddSeparator();
	m_toolbar->AddSeparator();
	m_matrice_associe = new wxButton(m_toolbar, ID_MA, wxT("Matrice Adjacence"));
	m_matrice_associe->SetToolTip(new wxToolTip(wxT("Matrice d'adjacence/d'incidence sommet-sommet")));
	m_toolbar->AddControl(m_matrice_associe, wxT("Matrice d'adjacence/d'incidence sommet-sommet"));
	m_matrice_incidence = new wxButton(m_toolbar, ID_MI, wxT("Matrice Incidence"));
	m_matrice_incidence->SetToolTip(new wxToolTip(wxT("Matrice d'incidence sommet-arc")));
	m_toolbar->AddControl(m_matrice_incidence, wxT("Matrice d'incidence sommet-arc"));
	m_matrice_valuation = new wxButton(m_toolbar, ID_MV, wxT("Matrice de valuation"));
	m_toolbar->AddControl(m_matrice_valuation);
	m_toolbar->Realize();
}

//------------------------------------------------------------------

void MainFrame::OnEffacer(wxCommandEvent& event)
{
	m_nb->graphe->efface_graphe();
	afficher_resultat_algorithme = false;
	m_nb->Refresh();
	m_nts->set_table(m_nb->graphe->get_graphe().list_successeur());
	m_nt->set_table(m_nb->graphe->get_graphe().list_successeur(), 
		m_nb->graphe->get_graphe().list_arcs());
	SetStatusText(wxT("Page vide"), 2);

}

//------------------------------------------------------------------

void MainFrame::OnMatriceValuation(wxCommandEvent& WXUNUSED(event))
{
	try {
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> g(m_nb->graphe->get_graphe());
		std::vector< std::vector<TYPE_VALEUR_LIEN> > v(m_nb->graphe->get_graphe().matrice_valuation());
		wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("Representation: matrice de valuation"),
			wxDefaultPosition, wxSize(100*v.size(), 80+30*v.size()));
		wxGrid* grid = new wxGrid(frame, wxID_ANY);
		grid->CreateGrid(v.size(), v.size());
		grid->SetRowLabelSize(50);
		grid->SetColLabelSize(25);
		grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
		grid->SetLabelFont(wxFont(9, wxFONTFAMILY_DEFAULT,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		for (uint i = 0; i < g.list_successeur().size(); ++i) {
			grid->SetRowLabelValue(i, to_string(g.list_successeur()[i][0]));
			grid->SetColLabelValue(i, to_string(g.list_successeur()[i][0]));
		}

		for (uint i = 0; i < v.size(); ++i)
			for (uint j = 0; j < v[i].size(); ++j) {
				if (v[i][j] == std::numeric_limits<TYPE_VALEUR_LIEN>::max())
					grid->SetCellValue(i, j, wxT("∞"));
				else
					grid->SetCellValue(i, j, to_string(v[i][j]));
				grid->SetCellAlignment(wxALIGN_CENTRE, i, j);
			}
		grid->EnableEditing(false);
		frame->SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
		frame->Centre();
		frame->Show(true);
	}
	catch (std::exception& err) {
		wxMessageBox(err.what(), wxT("Erreur"));
	}
}

//------------------------------------------------------------------

void MainFrame::OnMatriceAdjacence(wxCommandEvent& WXUNUSED(event))
{
	try {
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> g(m_nb->graphe->get_graphe());
		std::vector< std::vector<int> > v(m_nb->graphe->get_graphe().matrice_adjacence());
		wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("Representation: matrice adjacence sommet-sommet"),
			wxDefaultPosition, wxSize(100 * v.size(), 80 + 30 * v.size()));
		wxGrid* grid = new wxGrid(frame, wxID_ANY);
		grid->CreateGrid(v.size(), v.size());
		grid->SetRowLabelSize(50);
		grid->SetColLabelSize(25);
		grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
		grid->SetLabelFont(wxFont(9, wxFONTFAMILY_DEFAULT,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		for (uint i = 0; i < g.list_successeur().size(); ++i) {
			grid->SetRowLabelValue(i, to_string(g.list_successeur()[i][0]));
			grid->SetColLabelValue(i, to_string(g.list_successeur()[i][0]));
		}

		for (uint i = 0; i < v.size(); ++i)
			for (uint j = 0; j < v[i].size(); ++j) {
				grid->SetCellValue(i, j, to_string(v[i][j]));
				grid->SetCellAlignment(wxALIGN_CENTRE, i, j);
			}
		grid->EnableEditing(false);
		frame->SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
		frame->Centre();
		frame->Show(true);
	}
	catch (std::exception& err) {
		wxMessageBox(err.what(), wxT("Erreur"));
	}
}

//------------------------------------------------------------------

void MainFrame::OnMatriceIncidence(wxCommandEvent& WXUNUSED(event))
{
	try {
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> g(m_nb->graphe->get_graphe());
		std::vector< std::vector<int> > v(m_nb->graphe->get_graphe().matrice_incidence());
		wxFrame* frame = new wxFrame(NULL, wxID_ANY, wxT("Representation: matrice incidence sommet-arc"),
			wxDefaultPosition, wxSize(100 * v[0].size(), 80 + 30 * v.size()));
		wxGrid* grid = new wxGrid(frame, wxID_ANY);
		grid->CreateGrid(v.size(), v[0].size());
		grid->SetRowLabelSize(50);
		grid->SetColLabelSize(25);
		grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
		grid->SetLabelFont(wxFont(9, wxFONTFAMILY_DEFAULT,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		for (uint i = 0; i < g.list_successeur().size(); ++i) 
			grid->SetRowLabelValue(i, to_string(g.list_successeur()[i][0]));
		
		for (uint i = 0; i < v[0].size(); ++i)
			grid->SetColLabelValue(i, std::string("u") + to_string(i));

		for (uint i = 0; i < v.size(); ++i)
			for (uint j = 0; j < v[i].size(); ++j) {
				if (v[i][j] == -2)
					grid->SetCellValue(i, j, wxT("?"));
				else
					grid->SetCellValue(i, j, to_string(v[i][j]));
				grid->SetCellAlignment(wxALIGN_CENTRE, i, j);
			}
		grid->EnableEditing(false);
		frame->SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
		frame->Centre();
		frame->Show(true);
	}
	catch (std::exception& err) {
		wxMessageBox(err.what(), wxT("Erreur"));
	}
}

//------------------------------------------------------------------

void MainFrame::set_tool(bool type_graphe_oriente)
{
	this->SetLabel(wxString("Graphe : ") + to_string(type_graphe_oriente ? " oriente" : "non oriente"));
	if (type_graphe_oriente) {
		m_toolbar->EnableTool(ID_ARC, true);
		m_toolbar->EnableTool(ID_SUP_ARC, true);
		m_menubar->Enable(ID_ARC, true);
		m_menubar->Enable(ID_SUP_ARC, true);
		m_toolbar->EnableTool(ID_ARETE, false);
		m_toolbar->EnableTool(ID_SUP_ARETE, false);
		m_menubar->Enable(ID_ARETE, false);
		m_menubar->Enable(ID_SUP_ARETE, false);
	}
	else {
		m_toolbar->EnableTool(ID_ARC, false);
		m_toolbar->EnableTool(ID_SUP_ARC, false);
		m_menubar->Enable(ID_ARC, false);
		m_menubar->Enable(ID_SUP_ARC, false);
		m_toolbar->EnableTool(ID_ARETE, true);
		m_toolbar->EnableTool(ID_SUP_ARETE, true);
		m_menubar->Enable(ID_ARETE, true);
		m_menubar->Enable(ID_SUP_ARETE, true);
	}
	m_toolbar->EnableTool(ID_SOMMET, true);
	m_toolbar->EnableTool(ID_SUP_SOMMET, true);
	m_toolbar->EnableTool(ID_MOD_SOMMET, true);
	m_toolbar->EnableTool(ID_MOD_LIEN, true);
	m_toolbar->EnableTool(wxID_SAVE, true);
	//		m_toolbar->EnableTool(wxID_OPEN, true);
	m_menubar->Enable(ID_SOMMET, true);
	m_menubar->Enable(ID_SUP_SOMMET, true);
	m_menubar->Enable(ID_MOD_SOMMET, true);
	m_menubar->Enable(ID_MOD_LIEN, true);
	m_menubar->Enable(wxID_SAVE, true);
	//		m_menubar->Enable(wxID_OPEN, true);
	if (m_nb->IsFrozen()) {
		m_nb->Thaw(); m_nb->graphe->set_type_graphe(type_graphe_oriente ?
			Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::ORIENTE :
			Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::NON_ORIENTE);
		m_nb->graphe->set_scrollbar();
	}
	if (m_nts->IsFrozen()) m_nts->Thaw();
	if (m_nt->IsFrozen()) m_nt->Thaw(); m_nt->m_oriente = type_graphe_oriente;
	m_nt->set_name_table();
	bitmapDC = wxBitmap(wxSize(taille_contexte_peripherique.x - 50, taille_contexte_peripherique.y - 50));
	this->SetSize(this->GetSize() + wxSize(1, 0));
}

void MainFrame::OnNouveau(wxCommandEvent& WXUNUSED(event))
{
	if (pour_nouveau) {
		// pour l'enregistrement avant d'ouvrir une nouvele page
		wxMessageDialog* dlg = new wxMessageDialog(this, wxT("Voulez vous continue ?"), wxT("Nouvelle page"),
			wxYES_NO);
		if (dlg->ShowModal() == wxID_NO) 
			return;
		this->OnEffacer(wxCommandEvent(wxEVT_NULL));
		m_nb->Freeze();
		m_nts->Freeze();
		m_nt->Freeze();
	}

	Nouveau* n = new Nouveau();
	n->ShowModal();
	if (n->valider()) {
		taille_contexte_peripherique = n->taille();
		type_graphe_oriente = n->graphe_oriente();
		pour_nouveau = true;
		set_tool(type_graphe_oriente);
	}
	n->Destroy();
}

//------------------------------------------------------------------

bool MainFrame::enregistrement(wxString nf)
{
	wxFile* ofs = new wxFile(nf, wxFile::write);
	if (!ofs->IsOpened()) { wxLogMessage("Peux pas enregistrer le fichier"); return false; }
	wxString info;
	info << "tdc " << taille_contexte_peripherique.x << ' ' << taille_contexte_peripherique.y << '\n'
		<< "tg " << (m_nb->graphe->get_graphe().oriente() ? "1" : "0") << '\n'
		<< "Sommet { ";
	for (uint i = 0; i < m_nb->graphe->get_graphe().nombre_sommet(); ++i) {
		Graphe::Sommet<TYPE_VALEUR_SOMMET> s(m_nb->graphe->get_graphe().list_successeur()[i][0]);
		info << " ( " << to_string(s) << ' ' << s.position().x << ' ' << s.position().y << " ) ";
	}
	info << " }\n"
		<< "Arc { ";
	int add = m_nb->graphe->get_graphe().oriente() ? 1 : 2;
	for (uint i = 0; i < m_nb->graphe->get_graphe().nombre_arc(); i+=add) {
		Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> a(m_nb->graphe->get_graphe().list_arcs()[i]);
		info << " ( " << to_string(a.poid()) << ' ' << to_string(a.sommet_initial())
			<< ' ' << to_string(a.sommet_final()) << " ) ";
	}
	info << " }\n";
	ofs->Write(info);
	if (!ofs->Close()) {
		wxLogError("Peux pas fermer le fichier \".graphe\" crée pour enregistrement"); return false;
	}
	return true;
}

//------------------------------------------------------------------

void MainFrame::OnEnregistrer(wxCommandEvent& WXUNUSED(event))
{
	wxTextEntryDialog* d1 = new wxTextEntryDialog(NULL, wxT("Entrer le nom de l'image :"),
										wxT("Enregistrer"));
	std::string nom, nom_fichier;
	while (d1->ShowModal() == wxID_OK) {
		nom = d1->GetValue().ToStdString();
		if (nom.empty())
			wxMessageBox(wxT("Veuillez entrer un nom a l'image."), wxT("Nom invalide"));
		else {
			nom_fichier = nom;
			nom += ".png"; // extention de l'image
			nom_fichier += ".graphe";
			enregistrement(nom_fichier);
			m_nb->SetSize(taille_contexte_peripherique);
			namefile = nom;
			break;
		}
	}
}

//------------------------------------------------------------------

bool MainFrame::ouverture(wxString nf)
{
	std::ifstream ifs(nf.ToStdString().c_str());
	std::string tdc, tg;
	wxSize taille;
	bool type;

	ifs >> tdc >> taille.x >> taille.y >> tg >> type;
	if (!ifs || tdc != "tdc" || tg != "tg") { wxLogMessage("format du fichier incorrect"); return false; }

	Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> graphe( type ?
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::ORIENTE : 
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::NON_ORIENTE);
	std::string sommet, arc;
	char ch1 = 0, ch2 = 0;

	ifs >> sommet >> ch1;
	if (sommet != "Sommet" || ch1 != '{') { wxLogMessage("Debut de Sommet incorrect"); return false; }
	while (true) {
		Sommet<TYPE_VALEUR_SOMMET> s;
		if (!(ifs >> s)) break;
		graphe.add_sommet(s);
	}

	// fin boucle des sommets
	ifs.clear();
	if (ifs >> ch2 && ch2 != '}') { wxLogMessage("Fin de Sommet incorrect"); return false; }

	ifs >> arc >> ch1;
	if (arc != "Arc" || ch1 != '{') { wxLogMessage("Debut d'arc incorrect"); return false; }
	while (true) {
		Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> a;
		if (!(ifs >> a)) break;
		for (uint i = 0; i < graphe.nombre_sommet(); ++i) {
			if (a.sommet_initial() == a.sommet_final() && a.sommet_initial() == graphe.list_successeur()[i][0])
				a.sommets(std::make_pair(graphe.list_successeur()[i][0], graphe.list_successeur()[i][0]));
			else if (a.sommet_initial() == graphe.list_successeur()[i][0])
				a.sommets(std::make_pair(graphe.list_successeur()[i][0], a.sommet_final()));
			else if (a.sommet_final() == graphe.list_successeur()[i][0])
				a.sommets(std::make_pair(a.sommet_initial(), graphe.list_successeur()[i][0]));
		}

		if (type) graphe.add_arc(a);
		else graphe.add_arete(a);
	}

	// fin boucle des arcs
	ifs.clear();
	if (ifs >> ch2 && ch2 != '}') { wxLogMessage("Fin d'arc incorrect"); return false; }
	m_nb->graphe->efface_graphe();
	m_nb->graphe->get_graphe().set_type(type ?
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::ORIENTE :
		Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::NON_ORIENTE);

	for (uint i = 0; i < graphe.nombre_sommet(); ++i) {
		m_nb->graphe->get_graphe().add_sommet(graphe.list_successeur()[i][0]);
		m_nb->graphe->list_sommets.push_back(graphe.list_successeur()[i][0]);
	}
	int add = type ? 1 : 2;
	for (uint i = 0; i < graphe.nombre_arc(); i+=add) {
		m_nb->graphe->list_arc.push_back(graphe.list_arcs()[i]);
		if (type) {
			m_nb->graphe->get_graphe().add_arc(graphe.list_arcs()[i]);
		}
		else {
			m_nb->graphe->get_graphe().add_arete(graphe.list_arcs()[i]);
			Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> aa(graphe.list_arcs()[i].poid(),
				graphe.list_arcs()[i].sommet_final(),
				graphe.list_arcs()[i].sommet_initial());
			m_nb->graphe->list_arc.push_back(aa);
		}
	}
	taille_contexte_peripherique = taille;
	type_graphe_oriente = type;
	return true;
}

//------------------------------------------------------------------

void MainFrame::OnOuvrir(wxCommandEvent& WXUNUSED(event))
{
	if (pour_nouveau) {
		// pour l'enregistrement avant d'ouvrir une nouvele page
		wxMessageDialog* dlg = new wxMessageDialog(this, wxT("Voulez vous continue ?"), wxT("Autre Graphe"),
			wxYES_NO);
		if (dlg->ShowModal() == wxID_NO)
			return;
		this->OnEffacer(wxCommandEvent(wxEVT_NULL));
		m_nb->Freeze();
		m_nts->Freeze();
		m_nt->Freeze();
	}

	wxFileDialog
		ouvrirFileDialog(this, _(""), "", "",
		"Graphe_value (*.graphe)|*.graphe", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (ouvrirFileDialog.ShowModal() == wxID_OK) {
		wxFileInputStream input_stream(ouvrirFileDialog.GetPath());
		if (!input_stream.IsOk()) {
			wxLogError("peux pas ouvrir le fichier '%s'.", ouvrirFileDialog.GetPath());
			return;
		}
		if (ouverture(ouvrirFileDialog.GetPath())) {
			set_tool(type_graphe_oriente);
			pour_nouveau = true;
		}
		m_nts->set_table(m_nb->graphe->get_graphe().list_successeur());
		m_nt->set_table(m_nb->graphe->get_graphe().list_successeur(), 
						m_nb->graphe->get_graphe().list_arcs());
		this->SetSize(this->GetSize() + wxSize(-1, 0));
	}
}

//------------------------------------------------------------------

void MainFrame::OnQuitter(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

//------------------------------------------------------------------

void MainFrame::OnAide(wxCommandEvent& WXUNUSED(event))
{
	/*std::string lines, line;
	std::ifstream ifs("image/aide.html");
	while (ifs >> line) lines += line;
	wxFileSystem::AddHandler(new wxMemoryFSHandler);
	wxMemoryFSHandler::AddFile("aide.htm", lines);*/

	wxDialog dlg(NULL, -1, wxString(_("Aide")), wxDefaultPosition,
		wxSize(800, 600));
	wxHtmlWindow *html = new wxHtmlWindow(&dlg, -1);
	html->SetBorders(10);
	html->LoadPage("image/aide.html");
	html->SetScrollbars(1, 1, 1000, 1000);
	dlg.ShowModal();
}

//------------------------------------------------------------------

void MainFrame::OnApropos(wxCommandEvent& WXUNUSED(event))
{
	wxAboutDialogInfo info;
	info.SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
	info.SetName(_("Graphe"));
	info.SetVersion(_("v1.0 beta"));
	info.SetDescription(_("Se programme est basée sur le calcule du plus court chemin d'un graphe."));
	wxArrayString list_developper;
	list_developper.Add("Refes Nassim");
	list_developper.Add("Ould Miloud Mohamed");
	info.SetDevelopers(list_developper);
	info.SetDocWriters(list_developper);
	info.SetLicence("<Graphe> est un logiciel libre ; vous pouvez le diffuser et/ou le modifier suivant les termes de la Licence de la bibliotheque wxWindows telle que publiée par la Free Software Foundation ; soit la version 3 de cette licence, soit (à votre convenance) une version ultérieure.\nPour plus d'information sur la licence visitez http://www.wxwidgets.org/about/licence/ \n");
	wxAboutBox(info);
}

//------------------------------------------------------------------

void MainFrame::OnGenerer(wxCommandEvent& WXUNUSED(event))
{
	wxString s = m_source->GetValue();
	wxString d = m_dest->GetValue();

	try {
		wxString algo_name;
		Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type type;
		if (m_algorithme != NULL) {
			delete m_algorithme;
			m_algorithme = NULL;
		}
		if (mp_algorithme != NULL) {
			delete mp_algorithme;
			mp_algorithme = NULL;
		}
		try {
			if (m_choix_algo->GetSelection() == 0) {
				m_algorithme = new Algorithme::Court_chemin::Dijkstra<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>
					(m_nb->graphe->get_graphe(), Graphe::Sommet<TYPE_VALEUR_SOMMET>(s.ToStdString()));
				mp_algorithme = new Algorithme::Court_chemin::Dijkstra<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>
					(m_nb->graphe->get_graphe(), Graphe::Sommet<TYPE_VALEUR_SOMMET>(s.ToStdString()));
				algo_name << "Dijkstra";
				type = Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type::DIJKSTRA;
				mp_algo = false;
			}
			else if (m_choix_algo->GetSelection() == 1) {
				m_algorithme = new Algorithme::Court_chemin::BellmanFord<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>
					(m_nb->graphe->get_graphe(), Graphe::Sommet<TYPE_VALEUR_SOMMET>(s.ToStdString()));
				mp_algorithme = new Algorithme::Court_chemin::BellmanFord<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>
					(m_nb->graphe->get_graphe(), Graphe::Sommet<TYPE_VALEUR_SOMMET>(s.ToStdString()));
				algo_name << "BellmanFord";
				type = Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type::BELLMAN_FORD;
				mp_algo = false;
			}
			else if (m_choix_algo->GetSelection() == 2) {
				m_algorithme = new Algorithme::Court_chemin::Roy_floyd_warshall<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>
					(m_nb->graphe->get_graphe(), Graphe::Sommet<TYPE_VALEUR_SOMMET>(s.ToStdString()));
				algo_name << "Roy-Floyd-Warshall";
				type = Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type::ROY_FLOYD_WARSHALL;
				mp_algorithme = new Algorithme::Court_chemin::BellmanFord<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>
					(m_nb->graphe->get_graphe(), Graphe::Sommet<TYPE_VALEUR_SOMMET>(s.ToStdString()));
				mp_algo = true;
			}
			else
				throw std::runtime_error("Veuillez choisir un algorithme.");
		}
		catch (std::runtime_error& err) {
			wxMessageBox(wxString(err.what()), wxT("Error"));
			afficher_resultat_algorithme = false;
			return;
		}

		destinataire = Graphe::Sommet<TYPE_VALEUR_SOMMET>(d.ToStdString());

		TYPE_VALEUR_LIEN cout = m_algorithme->distance_dl_source_vers(destinataire);

		wxString msg;
		msg << "La distance du point de depart( " << s << " ) vers l'arrivé( " << d << " ) = " << cout << "\n";
		msg << "Temp de calcule = ( " << m_algorithme->temp_execution_seconds() << " s ) - ( " <<
			m_algorithme->temp_execution_milliseconds() << " ms )\n";
		msg << "Chemin = ";

		std::vector< Graphe::Sommet < TYPE_VALEUR_SOMMET > > v(mp_algo
			? mp_algorithme->parcour_dl_source_vers(destinataire) 
			: m_algorithme->parcour_dl_source_vers(destinataire));

		for (uint i = 0; i < v.size(); ++i) {
			msg << v[i].get();
			if (i < v.size() - 1)
				msg << " -> ";
			else if (i % 6 == 0)
				msg << "\n\t";
		}

		wxMessageBox(msg, wxString(wxT("Resultat: ") + algo_name));
		afficher_resultat_algorithme = true;
		if (mp_algo)
			Trace_Matrice* t = new Trace_Matrice(m_nb->graphe->get_graphe(),
			((Algorithme::Court_chemin::Roy_floyd_warshall<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>*)m_algorithme)->trace_matrice(), type);
		else
			Trace* t = new Trace(m_nb->graphe->get_graphe(), m_algorithme->trace(), type);

// autre parcours
		wxFrame* autre_parcour = new wxFrame(NULL, wxID_ANY, wxT("Tout autre parcours"), 
			wxDefaultPosition, wxSize(400, 400));
		wxGridSizer* gs = new wxGridSizer(4, 1, 5, 5);
		wxTextCtrl* ap1 = new wxTextCtrl(autre_parcour, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize,
			wxTE_MULTILINE | wxTE_READONLY);
		wxTextCtrl* ap2 = new wxTextCtrl(autre_parcour, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize,
			wxTE_MULTILINE | wxTE_READONLY);
		wxStaticText* st1 = new wxStaticText(autre_parcour, wxID_ANY,
			wxT("Tout les chemins avec meme distance(petit distances trouvé) : "));
		wxStaticText* st2 = new wxStaticText(autre_parcour, wxID_ANY,
			wxT("Tout les autres chemins possible dans le graphe : "));

		std::vector < std::pair< std::vector< Sommet<TYPE_VALEUR_SOMMET> >, TYPE_VALEUR_LIEN > > ap1_
			(mp_algorithme->autre_parcour_dl_source_vers(destinataire, type,
			Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type_parcour::MINIMUM));
		std::vector < std::pair< std::vector< Sommet<TYPE_VALEUR_SOMMET> >, TYPE_VALEUR_LIEN > > ap2_
			(mp_algorithme->autre_parcour_dl_source_vers(destinataire, type,
			Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type_parcour::TOUT));
		if (ap1_.size() == 0)
			ap1->AppendText(to_string("<Vide>"));
		else
			for (uint i = 0; i < ap1_.size(); ++i) {
				for (uint j = 0; j < ap1_[i].first.size(); ++j) {
					ap1->AppendText(to_string(ap1_[i].first[j]));
					if (j < ap1_[i].first.size()-1)
						ap1->AppendText(to_string(" -> "));
				}
				ap1->AppendText(to_string(" = ") + to_string(ap1_[i].second) + to_string("\n"));
			}
		if (ap2_.size() == 0)
			ap2->AppendText(to_string("<Vide>"));
		else
			for (uint i = 0; i < ap2_.size(); ++i) {
				for (uint j = 0; j < ap2_[i].first.size(); ++j) {
					ap2->AppendText(to_string(ap2_[i].first[j]));
					if (j < ap2_[i].first.size() - 1)
						ap2->AppendText(to_string(" -> "));
				}
				ap2->AppendText(to_string(" = ") + to_string(ap2_[i].second) + to_string("\n"));
			}
		gs->Add(st1, 1, wxALIGN_CENTER);
		gs->Add(ap1, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);
		gs->Add(st2, 1, wxALIGN_CENTER);
		gs->Add(ap2, 1, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, 10);
		autre_parcour->SetSizer(gs);
		autre_parcour->SetBackgroundColour(*wxWHITE);
		autre_parcour->Show(true);

		m_nb->Refresh();
	}
	catch (std::runtime_error& err) {
		wxMessageBox(wxString(err.what()), wxT("Error"));
		afficher_resultat_algorithme = false;
	}
}

//------------------------------------------------------------------

void MainFrame::OnSommet(wxCommandEvent& WXUNUSED(event))
{
	if (pair_sommet.size() == 1)
		wxMessageBox(wxT("Veuillez choisir un deuxieme sommet pour metre un lien !"),
		wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
	if (pair_sommet.size() == 0)  {
		ajoute_arete = false;
		supprimer_sommet = false;
		supprimer_arete = false;
		ajoute_sommet = true;
		afficher_resultat_algorithme = false;
		modifier_sommet = false;
		modifier_lien = false;
	}
}

//------------------------------------------------------------------

bool MainFrame::OnSommetClicked() const
{
	return ajoute_sommet;
}

//------------------------------------------------------------------

void MainFrame::OnSupSommet(wxCommandEvent& WXUNUSED(event))
{
	if (pair_sommet.size() == 1)
		wxMessageBox(wxT("Veuillez choisir un deuxieme sommet pour metre un lien !"),
		wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
	if (pair_sommet.size() == 0) {
		ajoute_arete = false;
		ajoute_sommet = false;
		supprimer_sommet = true;
		supprimer_arete = false;
		afficher_resultat_algorithme = false;
		modifier_sommet = false;
		modifier_lien = false;
	}
}

//------------------------------------------------------------------

bool MainFrame::OnSupSommetClicked() const
{
	return supprimer_sommet;
}

//------------------------------------------------------------------

void MainFrame::OnModSommet(wxCommandEvent& WXUNUSED(event))
{
	if (pair_sommet.size() == 1)
		wxMessageBox(wxT("Veuillez choisir un deuxieme sommet pour metre un lien !"),
		wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
	if (pair_sommet.size() == 0)  {
		ajoute_arete = false;
		supprimer_sommet = false;
		supprimer_arete = false;
		ajoute_sommet = false;
		afficher_resultat_algorithme = false;
		modifier_sommet = true;
		modifier_lien = false;
	}
}

//------------------------------------------------------------------

bool MainFrame::OnModSommetClicked() const
{
	return modifier_sommet;
}

//------------------------------------------------------------------

void MainFrame::OnArete(wxCommandEvent& WXUNUSED(event))
{
	if (pair_sommet.size() == 1)
		wxMessageBox(wxT("Veuillez choisir un deuxieme sommet pour metre un lien !"),
		wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
	if (pair_sommet.size() == 0) {
		ajoute_arete = true;
		ajoute_sommet = false;
		supprimer_sommet = false;
		supprimer_arete = false;
		afficher_resultat_algorithme = false;
		modifier_sommet = false;
		modifier_lien = false;
	}
}

//------------------------------------------------------------------

bool MainFrame::OnAreteClicked() const
{
	return ajoute_arete;
}

//------------------------------------------------------------------

void MainFrame::OnSupArete(wxCommandEvent& WXUNUSED(event))
{
	if (pair_sommet.size() == 1)
		wxMessageBox(wxT("Veuillez choisir un deuxieme sommet supprimer un lien !"),
		wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
	if (pair_sommet.size() == 0) {
		ajoute_arete = false;
		ajoute_sommet = false;
		supprimer_sommet = false;
		supprimer_arete = true;
		afficher_resultat_algorithme = false;
		modifier_sommet = false;
		modifier_lien = false;
	}
}

//------------------------------------------------------------------

bool MainFrame::OnSupAreteClicked() const
{
	return supprimer_arete;
}

//------------------------------------------------------------------

void MainFrame::OnModLien(wxCommandEvent& WXUNUSED(event))
{
	if (pair_sommet.size() == 1)
		wxMessageBox(wxT("Veuillez choisir un deuxieme sommet supprimer un lien !"),
		wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
	if (pair_sommet.size() == 0) {
		ajoute_arete = false;
		ajoute_sommet = false;
		supprimer_sommet = false;
		supprimer_arete = false;
		afficher_resultat_algorithme = false;
		modifier_sommet = false;
		modifier_lien = true;
	}
}

//------------------------------------------------------------------

bool MainFrame::OnModLienClicked() const
{
	return modifier_lien;
}

//------------------------------------------------------------------

std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> > 
MainFrame::parcour_algorithme(Graphe::Sommet<TYPE_VALEUR_SOMMET> d) const
{
	return m_algorithme->parcour_dl_source_vers(d);
}

//------------------------------------------------------------------

Graphe::Sommet< TYPE_VALEUR_SOMMET > MainFrame::get_destinataire() const
{
	return Graphe::Sommet< TYPE_VALEUR_SOMMET >(m_dest->GetValue().ToStdString());
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

BEGIN_EVENT_TABLE(Dessin_Graphe, wxScrolledCanvas)
	EVT_PAINT(Dessin_Graphe::OnPaint)
	EVT_ERASE_BACKGROUND(Dessin_Graphe::OnEraseBackground)
	EVT_MOTION(Dessin_Graphe::OnMotion)
	EVT_LEFT_DOWN(Dessin_Graphe::OnMotion)
	EVT_LEFT_UP(Dessin_Graphe::OnMotion)
	EVT_RIGHT_DOWN(Dessin_Graphe::OnMotion)
	EVT_RIGHT_UP(Dessin_Graphe::OnMotion)
	EVT_ERASE_BACKGROUND(Dessin_Graphe::OnErase)
	EVT_SCROLLWIN(Dessin_Graphe::OnScroll)
END_EVENT_TABLE()

//------------------------------------------------------------------

Dessin_Graphe::Dessin_Graphe(wxNotebook* parent)
: wxScrolledCanvas(parent, wxID_ANY),
	m_parent((MainFrame*)parent->GetParent()),
	graphe(m_parent->type_graphe_oriente ? 
		   Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::ORIENTE : 
		   Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::NON_ORIENTE),
		   graphe_resultat_algorithme(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::NON_ORIENTE),
		   ok(false)
{
	SetScrollbars(1, 1, m_parent->taille_contexte_peripherique.x, 
						m_parent->taille_contexte_peripherique.y);
	SetClientSize(m_parent->taille_contexte_peripherique);
	Centre();
}

//------------------------------------------------------------------

void Dessin_Graphe::set_scrollbar()
/*
	reglé le scrollbar de la fenetre
*/
{
	SetScrollbars(1, 1, m_parent->taille_contexte_peripherique.x,
		m_parent->taille_contexte_peripherique.y);
	SetClientSize(m_parent->taille_contexte_peripherique);
}

//------------------------------------------------------------------

void Dessin_Graphe::PaintBackground(wxDC& dc)
{
	wxColour backgroundColour = *wxWHITE/*GetBackgroundColour()*/;
	if (!backgroundColour.IsOk())
		backgroundColour = /*wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)*/*wxWHITE;
	dc.SetBrush(wxBrush(backgroundColour));
	dc.SetPen(wxPen(backgroundColour, 1));
	wxRect windowRect(wxPoint(0, 0), GetClientSize());
	CalcUnscrolledPosition(windowRect.x, windowRect.y,
		&windowRect.x, &windowRect.y);
	dc.DrawRectangle(windowRect);
}

//------------------------------------------------------------------

void Dessin_Graphe::dessiner_graphe_resultat_algorithme(wxDC& dc, wxPen lien, wxPen sommet, bool afficher_poid)
{
	dc.SetPen(sommet);
	for (uint i = 0; i < graphe_resultat_algorithme.list_successeur().size(); ++i) {
		Graphe::Sommet< TYPE_VALEUR_SOMMET > s(graphe_resultat_algorithme.list_successeur()[i][0]);
		s.dessiner(dc, i);
	}
	dc.SetPen(lien);

	uint countb = 1, counth = 1;
	bool v = false, w = false;

	for (uint i = 0; i < graphe_resultat_algorithme.list_arcs().size(); i += 2) {
		countb = counth = 1;
		v = w = false;

		for (uint j = 0; j < graphe.list_arcs().size(); graphe.oriente() ? ++j : j+=2) {
			if (graphe.list_arcs()[j].sommets().first == graphe_resultat_algorithme.list_arcs()[i].sommets().first &&
				graphe.list_arcs()[j].sommets().second == graphe_resultat_algorithme.list_arcs()[i].sommets().second) {
				if (v) countb += 2;
				else v = true;
				if (graphe.list_arcs()[j].poid() == graphe_resultat_algorithme.list_arcs()[i].poid()) {
					Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> aa(graphe.list_arcs()[j]);
					((Graphe::Arete<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>)aa).dessiner(dc, false, countb);
				}
			}
			else {
				if (graphe.non_oriente() &&
					graphe.list_arcs()[j].sommets().first == graphe_resultat_algorithme.list_arcs()[i].sommets().second &&
					graphe.list_arcs()[j].sommets().second == graphe_resultat_algorithme.list_arcs()[i].sommets().first) {
					if (w) counth += 2;
					else w = true;
					if (graphe.list_arcs()[j].poid() == graphe_resultat_algorithme.list_arcs()[i].poid()) {
						Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> aa(graphe.list_arcs()[j]);
						((Graphe::Arete<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>)aa).dessiner(dc, false, counth);
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------

void Dessin_Graphe::OnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc(this);
	dc.SetClippingRegion(wxRect(m_parent->taille_contexte_peripherique));
	PrepareDC(dc);
	PaintBackground(dc);
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.SetPen(*wxBLACK_PEN);
	// afficher le chemin resultant d'un algorithme choisi
	if (m_parent->afficher_resultat_algorithme) {
		while (graphe_resultat_algorithme.nombre_sommet() != 0)
			graphe_resultat_algorithme.del_sommet(graphe_resultat_algorithme.list_successeur()[0][0]);
		std::vector< Graphe::Sommet < TYPE_VALEUR_SOMMET > > v;
		if (m_parent->mp_algo)
			v = (m_parent->mp_algorithme->parcour_dl_source_vers(m_parent->destinataire));
		else
			v = (m_parent->m_algorithme->parcour_dl_source_vers(m_parent->destinataire));

		// avoir la position des sommets concerne
		for (uint i = 1; i < v.size(); ++i) {
			for (uint j = 0; j < graphe.nombre_sommet(); ++j) {
				if (v[i - 1] == graphe.list_successeur()[j][0])
					v[i - 1] = graphe.list_successeur()[j][0];
				else if (v[i] == graphe.list_successeur()[j][0]) 
					v[i] = graphe.list_successeur()[j][0];
			}
			graphe_resultat_algorithme.add_sommet(v[i - 1]);
			graphe_resultat_algorithme.add_sommet(v[i]);

			Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> aa(std::numeric_limits<TYPE_VALEUR_LIEN>::max(), 
																v[i - 1], v[i]);
			// avoir la plus petit valeur des liens entre pair de sommet
			for (uint j = 0; j < graphe.list_arcs().size(); ++j) {
				if (graphe.list_arcs()[j].sommets().first == v[i - 1] &&
					graphe.list_arcs()[j].sommets().second == v[i]) {
					if (aa.poid() == std::numeric_limits<TYPE_VALEUR_LIEN>::max())
						aa.set_poid(graphe.list_arcs()[j].poid());
					else if (graphe.list_arcs()[j].poid() < aa.poid())
						aa.set_poid(graphe.list_arcs()[j].poid());
				}
			}
			graphe_resultat_algorithme.add_arete(aa);
		}

		dessiner_graphe_resultat_algorithme(dc, wxPen(*wxBLUE, 6), wxPen(*wxBLUE, 6), false);
	}

	graphe.dessiner(dc, *wxRED_PEN, *wxBLACK_PEN, true);
	//m_parent->afficher_resultat_algorithme = false;

	wxMemoryDC memDC;
	memDC.SetClippingRegion(wxSize(m_parent->m_nb->graphe->GetClientSize()));
	memDC.SelectObject(m_parent->bitmapDC);
	memDC.Clear();
	// copier le graphe dessiné et le coller dans un bitmap
	memDC.Blit(0, 0, m_parent->m_nb->graphe->GetClientSize().x, 
		m_parent->m_nb->graphe->GetClientSize().y, &dc, 0, 0);
	memDC.SelectObject(wxNullBitmap);

	dc.SetPen(wxNullPen);
}

//------------------------------------------------------------------

void Dessin_Graphe::OnEraseBackground(wxEraseEvent& event)
{
}

//------------------------------------------------------------------

bool Dessin_Graphe::sommet_existe(std::string s)
{
	for (uint i = 0; i < list_sommets.size(); ++i)
		if (list_sommets[i].get() == s)
			return true;
	return false;
}

//------------------------------------------------------------------

std::vector< Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >::iterator
Dessin_Graphe::lien_existe(const Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>& a)
{
	typedef std::vector< Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >::iterator iter;
	iter i = list_arc.begin();
	if (m_parent->type_graphe_oriente) {
		for (; i != list_arc.end(); ++i)
			if (i->sommet_initial() == a.sommet_initial()
				&& i->sommet_final() == a.sommet_final())
				break;
	}
	else {
		for (; i != list_arc.end(); ++i)
			if ((i->sommets().first == a.sommets().first ||
				i->sommets().first == a.sommets().second)
				&& (i->sommets().second == a.sommets().second ||
				i->sommets().second == a.sommets().first))
				break;
	}
	return i;
}

//------------------------------------------------------------------

std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator Dessin_Graphe::sommet_existe_en_pos(wxPoint pos)
{
	typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
	iter i = list_sommets.begin();
	for (; i != list_sommets.end(); ++i)
		if (i->position().x - 20 <= pos.x &&
			pos.x <= i->position().x + 20 &&
			i->position().y - 20 <= pos.y &&
			pos.y <= i->position().y + 20)
		{
			break;
		}
	return i;
}

//------------------------------------------------------------------

void Dessin_Graphe::ajoute_sommet(wxDC& dc, wxMouseEvent& event)
{
	wxPoint pos = event.GetPosition();
	for (uint i = 0; i < list_sommets.size(); ++i) // eviter la collision entre sommet dans le dessin
		if (list_sommets[i].position().x - 40 <= pos.x &&
			pos.x <= list_sommets[i].position().x + 40 &&
			list_sommets[i].position().y - 40 <= pos.y &&
			pos.y <= list_sommets[i].position().y + 40)
		{
			wxMessageBox(wxT("Collision entre sommets !"), wxT("Sommet"), wxICON_EXCLAMATION);
			dc.SetPen(wxNullPen);
			return;
		}
	//------------------------------------------------------------
	wxTextEntryDialog* d1 = new wxTextEntryDialog(NULL, wxT("Entrer le nom du sommet :"), wxT("Nom Sommet"));
	std::string nom;
	while (d1->ShowModal() == wxID_OK) {
		nom = d1->GetValue().ToStdString();
		if (nom.empty())
			wxMessageBox(wxT("Veuillez entrer un nom au sommet."), wxT("Nom invalide"));
		else if (sommet_existe(nom))
			wxMessageBox(wxT("Ce nom existe deja.\nVeuillez entrer un autre nom."), wxT("Nom invalide"));
		else {
			// cree le sommet et l'ajouté au graphe
			Graphe::Sommet<TYPE_VALEUR_SOMMET> s(nom, event.GetPosition());
			graphe.add_sommet(s);
			list_sommets.push_back(s);
			//s.dessiner(dc, list_sommets.size() - 1);
			ok = true;
			m_parent->SetStatusText(wxT("Sommet Ajouter"), 2);
			break;
		}
	}
}

//------------------------------------------------------------------

void Dessin_Graphe::supprimer_sommet(wxMouseEvent& event)
{
	typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
	iter p = sommet_existe_en_pos(event.GetPosition());
	if (p != list_sommets.end())
	{
		graphe.del_sommet(*p);
		list_sommets.erase(p);
		ok = true;
		m_parent->SetStatusText(wxT("Sommet Supprimer"), 2);
		//Refresh();
	}
	else
		wxMessageBox(wxT("Ya pas de sommet on position que vous avez choisi."),
		wxT("Position invalide"),
		wxICON_EXCLAMATION);
}

//------------------------------------------------------------------

void Dessin_Graphe::modifier_sommet(wxMouseEvent& event)
	// renomé le sommet selectionné
{
	typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
	iter p = sommet_existe_en_pos(event.GetPosition());
	if (p != list_sommets.end()) // ya un sommet en position courante du curseur de souris
	{
		wxString text;
		text << "Veuillez entrer un nouveau nom au sommet<" << p->get() << "> :";
		wxTextEntryDialog* d1 = new wxTextEntryDialog(NULL, text, wxT("Modifier"));
		std::string nom;
		while (d1->ShowModal() == wxID_OK) {
			nom = d1->GetValue().ToStdString();
			if (nom.empty())
				wxMessageBox(wxT("Veuillez entrer un nom au sommet."), wxT("Nom invalide"));
			else if (sommet_existe(nom))
				wxMessageBox(wxT("Ce nom existe deja.\nVeuillez entrer un autre nom."), wxT("Nom invalide"));
			else {
				wxString prev = p->get();
				graphe.mod_sommet(*p, Sommet<TYPE_VALEUR_SOMMET>(nom, p->position()));

				for (int i = 0; i < list_arc.size(); ++i) {
					if (list_arc[i].sommets().first.get() == prev)
						list_arc[i].sommets(make_pair(Sommet<TYPE_VALEUR_SOMMET>(nom, p->position()),
						list_arc[i].sommets().second));
					else if (list_arc[i].sommets().second.get() == prev)
						list_arc[i].sommets(make_pair(list_arc[i].sommets().first,
						Sommet<TYPE_VALEUR_SOMMET>(nom, p->position())));
				}
				/*for (int i = 0; i < list_sommets.size(); ++i)
					if (list_sommets[i].get() == prev) {
						list_sommets[i].set(nom);
						list_sommets[i].position(p->position());
					}*/

				p->set(nom);

				ok = true;
				m_parent->SetStatusText(wxT("Sommet Modifier"), 2);
				break;
			}
		}
	}
	else
		wxMessageBox(wxT("Ya pas de sommet on position que vous avez choisi."),
		wxT("Position invalide"),
		wxICON_EXCLAMATION);
}

//------------------------------------------------------------------

void Dessin_Graphe::ajoute_arete(wxDC& dc, wxMouseEvent& event)
{
	typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
	iter p = sommet_existe_en_pos(event.GetPosition());
	if (p != list_sommets.end())
		m_parent->pair_sommet.push_back(Graphe::Sommet<TYPE_VALEUR_SOMMET>(p->get(), p->position()));
	else
		wxMessageBox(wxT("Ya pas de sommet on position que vous avez choisi."),
		wxT("Position invalide"),
		wxICON_EXCLAMATION);

	if (m_parent->pair_sommet.size() == 2) {
		wxTextEntryDialog* d1 = new wxTextEntryDialog(NULL, wxT("Entrer la valeur du lien :"), wxT("Valeur Lien"));
		std::string nom;
		while (d1->ShowModal() == wxID_OK) {
			if (d1->GetValue().Cmp(wxT("")) == 0)
				wxMessageBox(wxT("Veuillez entrer une valeur a l'arete."), wxT("valeur invalide"));
			else {
				Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> a(to_double(d1->GetValue().ToStdString()),
					m_parent->pair_sommet[0],
					m_parent->pair_sommet[1]);

				list_arc.push_back(a);
				ok = true;
				m_parent->SetStatusText(wxT("Lien Ajouter"), 2);
				if (m_parent->type_graphe_oriente) {
					graphe.add_arc(a);
				}
				else {
					graphe.add_arete(a);
					Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> aa(to_double(d1->GetValue().ToStdString()),
						m_parent->pair_sommet[1],
						m_parent->pair_sommet[0]);
					list_arc.push_back(aa);
				}

				break;
			}
		}
		while (m_parent->pair_sommet.size() != 0)
			m_parent->pair_sommet.pop_back();
	}
}

//------------------------------------------------------------------

void Dessin_Graphe::OnScroll(wxScrollWinEvent& event)
	// gere la position du curseur de souris
{
	if (event.GetOrientation() == wxVERTICAL)
		m_ajoute_a_sourie.y = event.GetPosition();
	if (event.GetOrientation() == wxHORIZONTAL)
		m_ajoute_a_sourie.x = event.GetPosition();
}

//------------------------------------------------------------------

void Dessin_Graphe::supprimer_arete(wxMouseEvent& event)
{
	typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
	iter p = sommet_existe_en_pos(event.GetPosition());
	if (p != list_sommets.end())
	{
		m_parent->pair_sommet.push_back(Graphe::Sommet<TYPE_VALEUR_SOMMET>(p->get(), p->position()));
	}
	else
		wxMessageBox(wxT("Ya pas de sommet on position que vous avez choisi."),
		wxT("Position invalide"),
		wxICON_EXCLAMATION);

	if (m_parent->pair_sommet.size() == 2) {
		Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> a(0, m_parent->pair_sommet[0],
			m_parent->pair_sommet[1]);

		// la liste des lien entre la pair de sommet selectionné
		std::vector< std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > > v;
		for (uint i = 0; i < graphe.nombre_arc(); ++i) {
			if (graphe.list_arcs()[i].sommets().first == a.sommets().first &&
				graphe.list_arcs()[i].sommets().second == a.sommets().second) {
				// position et lien
				if (m_parent->type_graphe_oriente)
					v.push_back(std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >(i, graphe.list_arcs()[i]));
				else {
					v.push_back(std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >(i / 2, graphe.list_arcs()[i]));
					if (a.sommets().first == a.sommets().second) ++i;
				}
			}
		}
		if (v.size() == 1) { // un seul lien entre pair de sommet
			if (m_parent->type_graphe_oriente)
				graphe.del_arc(v[0].second);
			else
				graphe.del_arete(v[0].second);
			for (uint i = 0; i < list_arc.size(); ++i)
				if (list_arc[i] == v[0].second &&
					list_arc[i].sommets().first == v[0].second.sommets().first &&
					list_arc[i].sommets().second == v[0].second.sommets().second) {
					list_arc.erase(list_arc.begin() + i);
					break;
				}
			ok = true;
			m_parent->SetStatusText(wxT("Lien Supprimer"), 2);
		}

		else if (v.size() != 0) { // plusieur lien entre pair de sommet
			Del_Lien* sup = new Del_Lien(v);
			sup->ShowModal();
			if (sup->valider()) {
				if (m_parent->type_graphe_oriente) {
					graphe.del_arc(v[sup->mon_choix()].second);
				}
				else {
					graphe.del_arete(v[sup->mon_choix()].second);
				}
				for (uint i = 0; i < list_arc.size(); ++i)
					if (list_arc[i] == v[sup->mon_choix()].second &&
						list_arc[i].sommets().first == v[sup->mon_choix()].second.sommets().first &&
						list_arc[i].sommets().second == v[sup->mon_choix()].second.sommets().second) {
						list_arc.erase(list_arc.begin() + i);
						break;
					}
				ok = true;
				m_parent->SetStatusText(wxT("Lien Supprimer"), 2);
			}
		}
		else // pas de lien entre pair de sommet
			wxMessageBox(wxT("Ya pas de lien entre les pairs de sommets que vous avez choisi."),
			wxT("Arete invalide"),
			wxICON_EXCLAMATION);

		while (m_parent->pair_sommet.size() != 0)
			m_parent->pair_sommet.pop_back();
	}
}

//------------------------------------------------------------------

void Dessin_Graphe::modifier_lien(wxMouseEvent& event)
{
	typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
	iter p = sommet_existe_en_pos(event.GetPosition());
	if (p != list_sommets.end())
	{
		m_parent->pair_sommet.push_back(Graphe::Sommet<TYPE_VALEUR_SOMMET>(p->get(), p->position()));
	}
	else
		wxMessageBox(wxT("Ya pas de sommet on position que vous avez choisi."),
		wxT("Position invalide"),
		wxICON_EXCLAMATION);

	if (m_parent->pair_sommet.size() == 2) {
		Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> a(0, m_parent->pair_sommet[0],
			m_parent->pair_sommet[1]);

		// la liste des lien entre la pair de sommet selectionné
		std::vector< std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > > v;
		for (uint i = 0; i < graphe.nombre_arc(); ++i) {
			if (graphe.list_arcs()[i].sommets().first == a.sommets().first &&
				graphe.list_arcs()[i].sommets().second == a.sommets().second) {
				// position et lien
				if (m_parent->type_graphe_oriente)
					v.push_back(std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >(i, graphe.list_arcs()[i]));
				else {
					v.push_back(std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> >(i / 2, graphe.list_arcs()[i]));
					if (a.sommets().first == a.sommets().second) ++i;
				}
			}
		}
		if (v.size() != 0) { // plusieur(1 ou +) lien entre pair de sommet
			Mod_Lien* sup = new Mod_Lien(v);
			sup->ShowModal();
			if (sup->valider()) {
				if (m_parent->type_graphe_oriente) {
					graphe.mod_lien(v[sup->mon_choix()].second, sup->ma_valeur());
				}
				else {
					Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> ss(v[sup->mon_choix()].second.poid(),
																		v[sup->mon_choix()].second.sommet_final(),
																		v[sup->mon_choix()].second.sommet_initial());
					graphe.mod_lien(v[sup->mon_choix()].second, sup->ma_valeur());
					graphe.mod_lien(ss, sup->ma_valeur());
				}
				for (uint i = 0; i < list_arc.size(); ++i)
					if (list_arc[i] == v[sup->mon_choix()].second &&
						list_arc[i].sommets().first == v[sup->mon_choix()].second.sommets().first &&
						list_arc[i].sommets().second == v[sup->mon_choix()].second.sommets().second) {
						list_arc.erase(list_arc.begin() + i);
						break;
					}
				ok = true;
				m_parent->SetStatusText(wxT("Lien Modifier"), 2);
			}
		}
		else // pas de lien entre pair de sommet
			wxMessageBox(wxT("Ya pas de lien entre les pairs de sommets que vous avez choisi."),
			wxT("Arete invalide"),
			wxICON_EXCLAMATION);

		while (m_parent->pair_sommet.size() != 0)
			m_parent->pair_sommet.pop_back();
	}
}

// ------------------------------------------------------------------

void Dessin_Graphe::OnMotion(wxMouseEvent& event)
{
	if (this->GetClientSize().x < m_parent->taille_contexte_peripherique.x &&
		this->GetClientSize().y < m_parent->taille_contexte_peripherique.y)
		//reglage de la position du curseur de souris
		event.SetPosition(wxPoint(event.GetPosition().x + m_ajoute_a_sourie.x,
						event.GetPosition().y + m_ajoute_a_sourie.y));
	if (event.Moving()) {
		// ya un sommet en position courante du curseur de souris
		wxString x;
		x << "pos(" << event.GetPosition().x << ", " << event.GetPosition().y << ")";
		m_parent->SetStatusText(x, 0);
		typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
		iter p = sommet_existe_en_pos(event.GetPosition());
		if (p != list_sommets.end()) {
			wxString xx;
			xx << "Sommet : " << to_string(p->get());
			m_parent->SetStatusText(xx, 1);
		}
		else {
			m_parent->SetStatusText(wxT(""), 1);
		}
	}
	wxClientDC dc(this);
	dc.SetClippingRegion(wxRect(m_parent->taille_contexte_peripherique));
	DoPrepareDC(dc);
	if (event.LeftDown()) {
		if ((event.GetPosition().x <= m_parent->taille_contexte_peripherique.x &&
			event.GetPosition().y <= m_parent->taille_contexte_peripherique.y))
		{
			// faire une action
			if (m_parent->OnSommetClicked()) {
				ajoute_sommet(dc, event);
			}
			else if (m_parent->OnSupSommetClicked()) {
				supprimer_sommet(event);
			}
			else if (m_parent->OnModSommetClicked()) {
				modifier_sommet(event);
			}
			else if (m_parent->OnAreteClicked()) {
				dc.SetPen(*wxRED_PEN);
				ajoute_arete(dc, event);
			}
			else if (m_parent->OnSupAreteClicked()) {
				dc.SetPen(*wxRED_PEN);
				supprimer_arete(event);
			}
			else if (m_parent->OnModLienClicked()) {
				modifier_lien(event);
			}
		}
		else
			wxMessageBox(wxT("Zone non aproprier pour le dessin."), wxT("Erreur"));
	}
	else {
		deplacer_sommet(event);
	}

	// pour evité le clignotement(Refresh(s)) du widget a chaque deplacement du curseur de souris
	if (ok) {
		m_parent->m_nts->set_table(graphe.list_successeur());
		m_parent->m_nt->set_table(graphe.list_successeur(), graphe.list_arcs());
		ok = false;
		Refresh();
	}

	if (!(m_parent->namefile).IsEmpty()) {
		(m_parent->bitmapDC).SaveFile(m_parent->namefile, wxBITMAP_TYPE_PNG);
		m_parent->namefile = "";
		m_parent->SetSize(m_parent->GetSize() + wxSize(0, 5));
		m_parent->SetSize(m_parent->GetSize() + wxSize(0, -5));
	}

	dc.SetPen(wxNullPen);
}

//------------------------------------------------------------------

void Dessin_Graphe::deplacer_sommet(wxMouseEvent& event)
/*
	modifier la postion d'un sommet
*/
{
	if (event.RightDown()) {
		if (m_parent->pair_sommet.size() == 1) {
			wxMessageBox(wxT("Veuillez choisir un deuxieme sommet pour metre un lien !"),
				wxT("Lien entre pair de sommet"), wxICON_EXCLAMATION);
			return;
		}
		// si ya pas une action en cour...
		// selectionné le sommet a deplacé
		typedef std::vector< Graphe::Sommet<TYPE_VALEUR_SOMMET> >::iterator iter;
		iter p = sommet_existe_en_pos(event.GetPosition());
		if (p != list_sommets.end()) {
			sd = p;
			sd->position(p->position());
		}
		else
			wxMessageBox(wxT("Ya pas de sommet on position que vous avez choisi."),
			wxT("Position invalide"),
			wxICON_EXCLAMATION);
	}
	else if (event.RightUp()) {
		// deplacé le sommet on lui affectant les nouvelles valeurs
		sd->position(event.GetPosition());
		graphe.mod_sommet(*sd, *sd);
		ok = true;
		m_parent->SetStatusText(wxT("Sommet Deplacer"), 2);
	}
}

//------------------------------------------------------------------

void Dessin_Graphe::OnErase(wxEraseEvent& event)
{

}

//------------------------------------------------------------------

Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>& Dessin_Graphe::get_graphe()
{
	return graphe;
}

//------------------------------------------------------------------

void Dessin_Graphe::set_type_graphe(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type t)
/*
	modifier le type du graphe
*/
{
	graphe.set_type(t);
}

//------------------------------------------------------------------

void Dessin_Graphe::efface_graphe()
{
	while (graphe.nombre_sommet() != 0) {
		graphe.del_sommet(graphe.list_successeur()[0][0]);
		list_sommets.pop_back();
	}

	while (graphe.nombre_arc() != 0) {
		graphe.del_arc(graphe.list_arcs()[0]);
		list_arc.pop_back();
	}
	
	Refresh();
}

//------------------------------------------------------------------

wxPoint Dessin_Graphe::scrollbar_pos() const
{
	return m_ajoute_a_sourie;
}

//------------------------------------------------------------------

BEGIN_EVENT_TABLE(Del_Lien, wxDialog)
	EVT_CHOICE(ID_CHOIX, Del_Lien::OnChoix)
	EVT_BUTTON(wxID_YES, Del_Lien::OnValider)
	EVT_BUTTON(wxID_NO, Del_Lien::OnAnnuler)
END_EVENT_TABLE()

//------------------------------------------------------------------

/*
	affichage de la liste de lien(arc/arete) a supprimer entre pair de sommet
*/

Del_Lien::Del_Lien(const std::vector< std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > >& v)
	: wxDialog(NULL, wxID_ANY, wxT("Choix du lien"), wxDefaultPosition, wxSize(400, 130)),
		m_lien_choisi(0)
{
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* text = new wxStaticText(this, wxID_ANY, wxT("Veuillez choisir le lien a supprimer: "));
	wxString table[1000];
	for (uint i = 0; i < v.size(); ++i) {
		wxString x;
		x << "u" << to_string(v[i].first) << " = " << to_string(v[i].second.poid());
		table[i] = x;
	}

	m_choix = new wxChoice(this, ID_CHOIX, wxDefaultPosition, wxDefaultSize,
		v.size(), table);
	m_ok = new wxButton(this, wxID_YES, wxT("Ok"));
	m_annuler = new wxButton(this, wxID_NO, wxT("Annuler"));

	hbox1->Add(text, 0, wxEXPAND | wxALL, 5);
	hbox1->Add(m_choix, 1, wxEXPAND | wxALL, 5);
	hbox2->Add(m_ok, 0, wxEXPAND | wxALL, 5);
	hbox2->Add(m_annuler, 0, wxEXPAND | wxALL, 5);

	vbox->Add(hbox1, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox2, 0, wxEXPAND | wxALL | wxALIGN_RIGHT, 5);
	this->SetSizer(vbox);
}

//------------------------------------------------------------------

void Del_Lien::OnChoix(wxCommandEvent& WXUNUSED(event))
{
	m_lien_choisi = m_choix->GetSelection();
}

//------------------------------------------------------------------

void Del_Lien::OnValider(wxCommandEvent& WXUNUSED(event))
{
	m_valider = true;
	EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

//------------------------------------------------------------------

void Del_Lien::OnAnnuler(wxCommandEvent& WXUNUSED(event))
{
	m_valider = false;
	EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

//------------------------------------------------------------------

inline bool Del_Lien::valider() const
{
	return m_valider;
}

//------------------------------------------------------------------

inline int Del_Lien::mon_choix() const
{
	return m_lien_choisi;
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

//------------------------------------------------------------------

BEGIN_EVENT_TABLE(Mod_Lien, wxDialog)
	EVT_CHOICE(ID_CHOIX, Mod_Lien::OnChoix)
	EVT_BUTTON(wxID_YES, Mod_Lien::OnValider)
	EVT_BUTTON(wxID_NO, Mod_Lien::OnAnnuler)
	EVT_SPINCTRLDOUBLE(wxID_EDIT, Mod_Lien::OnValeur)
END_EVENT_TABLE()

//------------------------------------------------------------------

Mod_Lien::Mod_Lien(const std::vector< std::pair< uint, Graphe::Arc<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> > >& v)
: wxDialog(NULL, wxID_ANY, wxT("Modifier"), wxDefaultPosition, wxSize(400, 170)),
m_lien_choisi(0)
{
	wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* text = new wxStaticText(this, wxID_ANY, wxT("Veuillez choisir le lien a supprimer: "));
	wxString table[1000];
	for (uint i = 0; i < v.size(); ++i) {
		wxString x;
		x << "u" << to_string(v[i].first) << " = " << to_string(v[i].second.poid());
		table[i] = x;
	}

	m_choix = new wxChoice(this, ID_CHOIX, wxDefaultPosition, wxDefaultSize,
		v.size(), table);
	m_choix->SetSelection(0);
	m_ok = new wxButton(this, wxID_YES, wxT("Ok"));
	m_annuler = new wxButton(this, wxID_NO, wxT("Annuler"));

	wxStaticText* text2 = new wxStaticText(this, wxID_ANY, wxT("Nouvelle valeur : "));
	m_mv = new wxSpinCtrlDouble(this, wxID_EDIT, to_string(v[0].second.poid()));
	m_mv->SetRange(-std::numeric_limits<TYPE_VALEUR_LIEN>::max(),
				   std::numeric_limits<TYPE_VALEUR_LIEN>::max());
	m_mv->SetIncrement(0.1);
	hbox1->Add(text, 0, wxEXPAND | wxALL, 5);
	hbox1->Add(m_choix, 1, wxEXPAND | wxALL, 5);
	hbox2->Add(m_ok, 0, wxEXPAND | wxALL, 5);
	hbox2->Add(m_annuler, 0, wxEXPAND | wxALL, 5);
	hbox3->Add(text2, 0, wxEXPAND | wxALL, 5);
	hbox3->Add(m_mv, 1, wxEXPAND | wxALL, 5);

	vbox->Add(hbox1, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox3, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox2, 0, wxEXPAND | wxALL | wxALIGN_RIGHT, 5);
	this->SetSizer(vbox);
}

//------------------------------------------------------------------

void Mod_Lien::OnChoix(wxCommandEvent& WXUNUSED(event))
{
	m_lien_choisi = m_choix->GetSelection();
}

//------------------------------------------------------------------

void Mod_Lien::OnValider(wxCommandEvent& WXUNUSED(event))
{
	m_valider = true;
	EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

//------------------------------------------------------------------

void Mod_Lien::OnAnnuler(wxCommandEvent& WXUNUSED(event))
{
	m_valider = false;
	EndModal(wxEVT_WINDOW_MODAL_DIALOG_CLOSED);
}

//------------------------------------------------------------------

inline bool Mod_Lien::valider() const
{
	return m_valider;
}

//------------------------------------------------------------------

inline int Mod_Lien::mon_choix() const
{
	return m_lien_choisi;
}

//------------------------------------------------------------------

inline double Mod_Lien::ma_valeur() const
{
	return m_valeur;
}

//------------------------------------------------------------------

void Mod_Lien::OnValeur(wxSpinDoubleEvent& event)
{
	m_valeur = m_mv->GetValue();
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

Trace::Trace(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> g,
				std::vector< std::vector<TYPE_VALEUR_LIEN> > v,
				Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type t)
	: wxFrame(NULL, wxID_ANY, wxT("Tracé des etapes de l'algorithme"),
	wxDefaultPosition, wxSize(100 * g.nombre_sommet(), 80 + 30 * v.size()))
{
	typedef Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type ACCT;
	try {
		wxGrid* grid = new wxGrid(this, wxID_ANY);
		grid->CreateGrid(v.size(), g.nombre_sommet());
		grid->SetRowLabelSize(50);
		grid->SetColLabelSize(25);
		grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
		grid->SetLabelFont(wxFont(9, wxFONTFAMILY_DEFAULT,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		for (uint i = 0; i < g.nombre_sommet(); ++i)
			grid->SetColLabelValue(i, to_string(g.list_successeur()[i][0]));
		for (uint i = 0; i < v.size(); ++i)
			if (t == ACCT::DIJKSTRA) {
				if (v[i][0] == std::numeric_limits<TYPE_VALEUR_LIEN>::max())
					grid->SetRowLabelValue(i, " ");
				else
					grid->SetRowLabelValue(i, to_string(g.list_successeur()[(int)v[i][0]][0]));
			}
			else if (t == ACCT::BELLMAN_FORD) {
				grid->SetRowLabelValue(i, " ");
			}

		for (uint i = 0; i < v.size(); ++i) {
			for (uint j = 1; j < v[i].size(); ++j) {
				if (t == ACCT::DIJKSTRA && j - 1 == v[i][0] && i != 0)
					grid->SetCellBackgroundColour(i-1, j-1, *wxCYAN);
				else if (t == ACCT::BELLMAN_FORD && i != 0 && v[i][j] != v[i-1][j])
					grid->SetCellBackgroundColour(i, j - 1, *wxCYAN);
				if (v[i][j] == std::numeric_limits<TYPE_VALEUR_LIEN>::max())
					grid->SetCellValue(i, j - 1, wxT("∞"));
				else
					grid->SetCellValue(i, j - 1, to_string(v[i][j]));
				grid->SetCellAlignment(wxALIGN_CENTRE, i, j - 1);
			}
		}
		grid->EnableEditing(false);
		this->SetIcon(wxIcon(wxT("image/graphe.ico"), wxBITMAP_TYPE_ICO));
		this->Centre();
		this->Show(true);
	}
	catch (std::exception& err) {
		wxMessageBox(err.what(), wxT("Erreur"));
	}
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

BEGIN_EVENT_TABLE(Trace_Matrice, wxFrame)
	EVT_BUTTON(ID_PRECEDENT, Trace_Matrice::OnPrecedent)
	EVT_BUTTON(ID_SUIVANT, Trace_Matrice::OnSuivant)
	EVT_BUTTON(ID_TERMINER, Trace_Matrice::OnTerminer)
END_EVENT_TABLE()

Trace_Matrice::Trace_Matrice(Graphe_value<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET> g,
	std::vector< std::vector< std::vector<TYPE_VALEUR_LIEN> > > v,
	Algorithme::Court_chemin::ACC<TYPE_VALEUR_LIEN, TYPE_VALEUR_SOMMET>::Type t)
	: wxFrame(NULL, wxID_ANY, wxT("Tracé des etapes de l'algorithme"), 
			wxDefaultPosition, wxSize(410, 260)),
	m_iteration_count(0),
	m_dernier_iteration(v.size()-1),
	m_v(v)
{
	try {
		wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
		wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
		m_grid = new wxGrid(this, wxID_ANY);
		m_grid->CreateGrid(g.nombre_sommet(), g.nombre_sommet());
		m_grid->SetRowLabelSize(50);
		m_grid->SetColLabelSize(25);
		m_grid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
		m_grid->SetLabelFont(wxFont(9, wxFONTFAMILY_DEFAULT,
			wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

		for (uint i = 0; i < g.nombre_sommet(); ++i) {
			m_grid->SetColLabelValue(i, to_string(g.list_successeur()[i][0]));
			m_grid->SetRowLabelValue(i, to_string(g.list_successeur()[i][0]));
		}

		m_iteration = new wxStaticText(this, wxID_ANY, wxT(""));
		m_iteration->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD));
		m_precedent = new wxButton(this, ID_PRECEDENT, wxT("Precedent"));
		m_suivant = new wxButton(this, ID_SUIVANT, wxT("Suivant"));
		m_terminer = new wxButton(this, ID_TERMINER, wxT("Terminer"));

		vbox->Add(m_iteration, 0, wxALL | wxALIGN_CENTRE, 10);
		vbox->Add(m_grid, 1, wxEXPAND | wxALL | wxALIGN_CENTRE, 10);

		hbox->Add(m_precedent, 0, wxALL | wxALIGN_CENTRE, 5);
		hbox->Add(m_suivant, 0, wxALL | wxALIGN_CENTRE, 5);
		hbox->Add(m_terminer, 0, wxALL | wxALIGN_CENTRE, 5);

		vbox->Add(hbox, 0, wxALL | wxALIGN_RIGHT, 10);

		SetSizer(vbox);
		Show(true);
		SetBackgroundColour(*wxWHITE);
		Centre();
		this->SetMinSize(wxSize(410, 260));

		m_precedent->Enable(false);
		m_terminer->Enable(false);
		set();
	}
	catch (std::exception& err) {
		wxLogError(err.what(), wxT("Erreur"));
	}
}

//------------------------------------------------------------------

void Trace_Matrice::OnPrecedent(wxCommandEvent& WXUNUSED(event))
{
	--m_iteration_count;
	if (m_iteration_count == m_dernier_iteration - 1) {
		m_suivant->Enable(true);
		m_terminer->Enable(false);
	}
	if (m_iteration_count == 0)
		m_precedent->Enable(false);

	set();
}

//------------------------------------------------------------------

void Trace_Matrice::OnSuivant(wxCommandEvent& WXUNUSED(event))
{
	++m_iteration_count;
	if (m_iteration_count == 1)
		m_precedent->Enable(true);
	if (m_iteration_count == m_dernier_iteration) {
		m_terminer->Enable(true);
		m_suivant->Enable(false);
	}

	set();
}

//------------------------------------------------------------------

void Trace_Matrice::OnTerminer(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

//------------------------------------------------------------------

void Trace_Matrice::set()
{
	wxString x;
	x << "Iteration = " << m_iteration_count << " / " << m_dernier_iteration;
	m_iteration->SetLabel(x);
	for (uint i = 0; i < m_dernier_iteration+1; ++i) {
		for (uint j = 0; j < m_dernier_iteration+1; ++j) {
			if (m_v[m_iteration_count][i][j] == std::numeric_limits<TYPE_VALEUR_LIEN>::max())
				m_grid->SetCellValue(i, j, wxT("∞"));
			else
				m_grid->SetCellValue(i, j, to_string(m_v[m_iteration_count][i][j]));
			m_grid->SetCellAlignment(wxALIGN_CENTRE, i, j);
		}
	}
}

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
