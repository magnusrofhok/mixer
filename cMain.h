#pragma once
#include "wx/wx.h"
#include "cTransparentStaticText.h"
#include <wx/numdlg.h>
#include <wx/valnum.h>
#include <iostream>
//#include <vector>
//#include <algorithm>


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	
	wxButton* m_CountBtn = nullptr;
	wxButton* m_QuitBtn = nullptr;
	wxTextCtrl* m_txtStartVolym = nullptr;
	wxTextCtrl* m_txtStartProcent = nullptr;
	wxTextCtrl* m_txtSlutProcent = nullptr;
	wxTextCtrl* m_list1 = nullptr;
	TransparentStaticText* m_textVolym = nullptr;
	TransparentStaticText* m_textStartProcent = nullptr;
	TransparentStaticText* m_textSlutProcent = nullptr;
	TransparentStaticText* m_textVolymAttBlanda = nullptr;
	wxPanel* m_panel2 = nullptr;
	wxBoxSizer* sizer = nullptr;
	wxPanel* m_panel1 = nullptr;
	void QuitButton(wxCommandEvent& evt);
	void CountButton(wxCommandEvent& evt);

	float roundTwoDecimals(float var)
	{
		float value = (int)(var * 100 + .5);
		return (float)value / 100;
	}

	wxDECLARE_EVENT_TABLE();
};

