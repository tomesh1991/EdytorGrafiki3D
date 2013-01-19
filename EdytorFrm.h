///-----------------------------------------------------------------
///
/// @file      EdytorFrm.h
/// @author    Mateusz "Mefioo" Knapczyk
/// Created:   2013-01-19 11:44:29
/// @section   DESCRIPTION
///            EdytorFrm class declaration
///
///------------------------------------------------------------------

#ifndef __EDYTORFRM_H__
#define __EDYTORFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
////Header Include End

////Dialog Style Start
#undef EdytorFrm_STYLE
#define EdytorFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxCLOSE_BOX
////Dialog Style End

class EdytorFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		EdytorFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Edytor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = EdytorFrm_STYLE);
		virtual ~EdytorFrm();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *WxEdit1;
		wxListBox *WxListBox1;
		wxPanel *WxPanel4;
		wxPanel *WxPanel3;
		wxPanel *WxPanel2;
		wxPanel *WxPanel1;
		wxGridSizer *WxGridSizer1;
		wxBoxSizer *WxBoxSizer2;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXEDIT1 = 1003,
			ID_WXLISTBOX1 = 1010,
			ID_WXPANEL4 = 1016,
			ID_WXPANEL3 = 1015,
			ID_WXPANEL2 = 1014,
			ID_WXPANEL1 = 1013,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
