#include "mainframe.h"

class MyApp : public wxApp
{
public :
	MainFrame* _frame; // fenetre principale 

	bool OnInit()
	{
		if (!wxApp::OnInit())
			return false;

		try {
			_frame = new MainFrame();
			_frame->Show(true); // afficher la fenetre
		}
		catch (std::runtime_error& err) {
			wxMessageBox(wxString(err.what()), wxT("Error"));
		}
		return true;
	};
};

DECLARE_APP(MyApp)
IMPLEMENT_APP(MyApp)