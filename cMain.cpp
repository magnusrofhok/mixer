#include "cMain.h"
#include "cTransparentStaticText.h"


wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, cMain::QuitButton)
EVT_BUTTON(10003, cMain::CountButton)
wxEND_EVENT_TABLE()

int const SCREENWITDH = 800;
int const SCREENHEIGHT = 640;
wxFont myFont(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
int const spacing = 170;

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Mixer", wxPoint(200, 200), wxSize(SCREENWITDH, SCREENHEIGHT))
{
	m_panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(SCREENWITDH, SCREENHEIGHT));
	m_panel1->SetBackgroundColour(wxColor(51, 153, 255));
	m_QuitBtn = new wxButton(this, 10001, "Avsluta", wxPoint(SCREENWITDH / 2 - 125, SCREENHEIGHT / 3 + 250), wxSize(250, 100)); m_QuitBtn->SetFont(myFont);
	m_CountBtn = new wxButton(this, 10003, "Rakna", wxPoint(SCREENWITDH / 2 - 125, SCREENHEIGHT / 3 + 125), wxSize(250, 100));m_CountBtn->SetFont(myFont);
	m_txtStartVolym = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 50), wxSize(120, 40),wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC)); m_txtStartVolym->SetFont(myFont);
	m_txtStartProcent = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 100), wxSize(120, 40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC)); m_txtStartProcent->SetFont(myFont);
	m_txtSlutProcent = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 150), wxSize(120, 40), wxTE_PROCESS_ENTER, wxTextValidator(wxFILTER_NUMERIC)); m_txtSlutProcent->SetFont(myFont);
	m_textVolym = new TransparentStaticText(this, wxID_ANY, wxT("Start Volym i Liter"), wxPoint(spacing, 52), wxSize(350, 50)); m_textVolym->SetFont(myFont);
	m_textStartProcent = new TransparentStaticText(this, wxID_ANY, wxT("Start procent"), wxPoint(spacing, 102), wxSize(350, 50)); m_textStartProcent->SetFont(myFont);
	m_textSlutProcent = new TransparentStaticText(this, wxID_ANY, wxT("Slut procent"), wxPoint(spacing, 152), wxSize(350, 50));m_textSlutProcent->SetFont(myFont);
	m_textVolymAttBlanda = new TransparentStaticText(this, wxID_ANY, wxT("Volym att blanda i"), wxPoint(spacing, 202), wxSize(350, 50));m_textVolymAttBlanda->SetFont(myFont);
	//m_list1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(20, 200), wxSize(120, 40), wxTE_READONLY);m_list1->SetFont(myFont);
	sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_panel1, 1, wxEXPAND | wxALL, 5);

	this->SetSizerAndFit(sizer);
}


//Startvolym * startprocent / slutprocent - startvolym

void cMain::CountButton(wxCommandEvent& evt)
{
	std::string m_txtStartVolymChanged (m_txtStartVolym->GetValue());
	std::cout << m_txtStartVolymChanged << std::endl;
	int position = m_txtStartVolymChanged.find(",");
	while (position != std::string::npos)
	{
		m_txtStartVolymChanged.replace(position, 1, ".");
		position = m_txtStartVolymChanged.find(",", position + 1);
	}

	std::string m_txtStartProcentChanged(m_txtStartProcent->GetValue());
	int position2 = m_txtStartProcentChanged.find(",");
	while (position2 != std::string::npos)
	{
		m_txtStartProcentChanged.replace(position2, 1, ".");
		position2 = m_txtStartProcentChanged.find(",", position2 + 1);
	}

	std::string  m_txtSlutProcentChanged(m_txtSlutProcent->GetValue());
	int position3= m_txtSlutProcentChanged.find(",");
	while (position3 != std::string::npos)
	{
		m_txtSlutProcentChanged.replace(position3, 1, ".");
		position3 = m_txtSlutProcentChanged.find(",", position3 + 1);
	}

	float num1 = std::stof(m_txtStartVolymChanged);
	float num2 = std::stof(m_txtStartProcentChanged);
	float num3 = std::stof(m_txtSlutProcentChanged);
	
	float i = ((num1 * num2) / num3) - num1;
	//float i = 5.4354;

	//m_list1->SetLabelText(std::to_string(roundTwoDecimals(i)));
	//m_list1->Update();
	
	m_list1 = new wxTextCtrl(this, wxID_ANY, std::to_string(roundTwoDecimals(i)), wxPoint(20, 200), wxSize(120, 40), wxTE_READONLY);m_list1->SetFont(myFont);
	
	std::cout << roundTwoDecimals(i) << std::endl;
	evt.Skip();
}

cMain::~cMain() {}

void cMain::QuitButton(wxCommandEvent& evt)
{
	Close(TRUE);
	evt.Skip();
}

