//
//Mixing fluids program
//

#include <wx/wxprec.h>
#include <wx/font.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
const int SCREENWITDH = 1366;
const int SCREENHEIGHT = 768;
const int spacing = 170;
//wxFont myFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);


class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
        wxPanel* m_panel1 = NULL;
	wxButton* m_QuitButton = NULL;
	wxButton* m_CountButton = NULL;

	wxTextCtrl* m_txtStartVolym = NULL;
	wxTextCtrl* m_txtStartProcent = NULL;
	wxTextCtrl* m_txtSlutProcent = NULL;
	wxTextCtrl* m_list1 = NULL;

	wxStaticText* m_textVolym = NULL;
	wxStaticText* m_textStartProcent = NULL;
	wxStaticText* m_textSlutProcent = NULL;
	wxStaticText* m_textVolymAttBlanda = NULL;

	wxBoxSizer* sizer = NULL;

	void QuitButton(wxCommandEvent& evt){Close(TRUE); evt.Skip();}
	void CountButton(wxCommandEvent& evt);
	std::string replaceComma(std::string str);
	float roundTwoDecimals(float var);
	std::string truncate(std::string str, size_t width);

private:
    void OnExit(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(wxID_EXIT,  MyFrame::OnExit)
    EVT_BUTTON(10001, MyFrame::QuitButton)
    EVT_BUTTON(10002, MyFrame::CountButton)
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Mixer", wxPoint(0, 0), wxSize(SCREENWITDH, SCREENHEIGHT) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxFont myFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(size));
	m_panel1->SetBackgroundColour(wxColor(51,153,255));
	m_QuitButton = new wxButton(this, 10001, "Avsluta", wxPoint(SCREENWITDH / 2 - 125, SCREENHEIGHT / 3 + 250), wxSize(250,100));m_QuitButton->SetFont(myFont);
	m_CountButton = new wxButton(this, 10002, "Kalkylera", wxPoint(SCREENWITDH / 2 - 125, SCREENHEIGHT / 3 + 125), wxSize(250,100));m_CountButton->SetFont(myFont);
	m_txtStartVolym = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20,50), wxSize(120,40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));m_txtStartVolym->SetFont(myFont);
	m_txtStartProcent = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20,100), wxSize(120,40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));m_txtStartProcent->SetFont(myFont);
	m_txtSlutProcent = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20,150), wxSize(120,40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));m_txtSlutProcent->SetFont(myFont);
	m_textVolym = new wxStaticText(this, wxID_ANY,"Start Volym i Liter", wxPoint(spacing, 52), wxSize(350, 50));m_textVolym->SetFont(myFont);
	m_textStartProcent = new wxStaticText(this, wxID_ANY,"Start Procent", wxPoint(spacing, 102), wxSize(350, 50));m_textStartProcent->SetFont(myFont);
	m_textSlutProcent = new wxStaticText(this, wxID_ANY,"Slut Procent", wxPoint(spacing, 152), wxSize(350, 50));m_textSlutProcent->SetFont(myFont);
	m_textVolymAttBlanda = new wxStaticText(this, wxID_ANY,"Volym att blanda i", wxPoint(spacing, 202), wxSize(350, 50));m_textVolymAttBlanda->SetFont(myFont);
	m_list1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20,200), wxSize(120,40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));m_list1->SetFont(myFont);

	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_panel1, 1, wxEXPAND | wxALL, 5);
	this->SetSizerAndFit(sizer);
}
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::CountButton(wxCommandEvent& evt)
{
	wxFont myFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	std::string m_txtStartVolymChanged(m_txtStartVolym->GetValue());
	std::string m_txtStartProcentChanged(m_txtStartProcent->GetValue());
	std::string m_txtSlutProcentChanged(m_txtSlutProcent->GetValue());
	float num1 = std::stof(replaceComma(m_txtStartVolymChanged));
	float num2 = std::stof(replaceComma(m_txtStartProcentChanged));
	float num3 = std::stof(replaceComma(m_txtSlutProcentChanged));

	float i = ((num1 * num2) / num3) - num1;

	m_list1 = new wxTextCtrl(this, wxID_ANY, truncate(std::to_string(i),4), wxPoint(20,200), wxSize(120,40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC));m_list1->SetFont(myFont);
	evt.Skip();
}

//Functions

std::string MyFrame::replaceComma(std::string str)
{
	int var = str.find(",");
	while (var != std::string::npos)
	{
		str.replace(var, 1, ".");
		var = str.find(",", var + 1);
	}
	return str;
}
float MyFrame::roundTwoDecimals(float var)
{
	float value = (int)(var * 100 + .5);
	return (float)value / 100;
}
std::string MyFrame::truncate(std::string str, size_t width)
{
	if (str.length() > width)
		return str.substr(0, width);
	return str;
}
