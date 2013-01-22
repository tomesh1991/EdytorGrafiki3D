///-----------------------------------------------------------------
///
/// @file      EdytorFrm.cpp
/// @author    Mateusz "Mefioo" Knapczyk
/// Created:   2013-01-19 11:44:29
/// @section   DESCRIPTION
///            EdytorFrm class implementation
///
///------------------------------------------------------------------

#include "EdytorFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// EdytorFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(EdytorFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(EdytorFrm::OnClose)
	EVT_TEXT_ENTER(ID_WXEDIT1,EdytorFrm::WxEdit1Enter)
END_EVENT_TABLE()
////Event Table End

EdytorFrm::EdytorFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

EdytorFrm::~EdytorFrm()
{
}

void EdytorFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxGridSizer1 = new wxGridSizer(0, 2, 0, 0);
	WxBoxSizer2->Add(WxGridSizer1, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(300, 300));
	WxGridSizer1->Add(WxPanel1, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxPanel2 = new wxPanel(this, ID_WXPANEL2, wxPoint(315, 5), wxSize(300, 300));
	WxGridSizer1->Add(WxPanel2, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxPanel3 = new wxPanel(this, ID_WXPANEL3, wxPoint(5, 315), wxSize(300, 300));
	WxGridSizer1->Add(WxPanel3, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxPanel4 = new wxPanel(this, ID_WXPANEL4, wxPoint(315, 315), wxSize(300, 300));
	WxGridSizer1->Add(WxPanel4, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	wxArrayString arrayStringFor_WxListBox1;
	WxListBox1 = new wxListBox(this, ID_WXLISTBOX1, wxPoint(635, 266), wxSize(300, 97), arrayStringFor_WxListBox1, wxLB_SINGLE);
	WxBoxSizer2->Add(WxListBox1, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("WxEdit1"), wxPoint(414, 645), wxSize(121, 19), 0, wxDefaultValidator, _("WxEdit1"));
	WxBoxSizer1->Add(WxEdit1, 0, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	SetTitle(_("Edytor grafiki 3D"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End
	
	index = 1;
	position = 0;
	__col = RGBCol(0,0,0);
	fac = new Factory();
	ch = NULL;
	for(int i=0;i<100;++i) access[i] = true;
	WxEdit1->Clear();
	WxEdit1->SetFocus();
}

void EdytorFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void EdytorFrm::MoveSolid(Solid* sol, double* params) {
    //PROSZE MI TO NAKURWIC BO JA JUZ NIE MOOOOOOOGE   
}

void EdytorFrm::RotateSolid(Solid* sol, double* params) {
    //PROSZE MI TO NAKURWIC BO JA JUZ NIE MOOOOOOOGE   
}

void EdytorFrm::SaveSolid(string file_name) {
    //PROSZE MI TO NAKURWIC BO JA JUZ NIE MOOOOOOOGE   
}

void EdytorFrm::LoadSolid(string file_name) {
    //PROSZE MI TO NAKURWIC BO JA JUZ NIE MOOOOOOOGE   
}

void EdytorFrm::rest(string str) {
    if(str == "clear_all"){
        WxListBox1->Clear();
        for(int i=0;i<100;++i) {
            if(!access[i]){
                delete SolArr[i];
                access[i] = true;
            }
        }
    }
    else {
    Chain* tmp_chain = new Chain(str);
    if(tmp_chain->getSplStr()->front() == "save") SaveSolid(tmp_chain->getSplStr()->at(1));
    if(tmp_chain->getSplStr()->front() == "load") LoadSolid(tmp_chain->getSplStr()->at(1));
    delete tmp_chain;    
    }
}

/*
 * WxEdit1Enter
 */
void EdytorFrm::WxEdit1Enter(wxCommandEvent& event)
{
    ch = new Chain(WxEdit1->GetLineText(0).ToStdString());
    double* params = ch->solve();
    int tmp_index = 0;
    int tmpID = 0;
    wxString stmp;
    while(!access[tmp_index]) tmp_index++;
    if(tmp_index<100){
        wxString* str = new wxString();
        switch((int)params[0]) {
            case  1 :   SolArr[tmp_index] = fac->produce(tmp_index,__col,params);
                        if(SolArr[tmp_index]!=NULL) {
                            (*str) << SolArr[tmp_index]->toList().c_str();
                        	WxListBox1->InsertItems(1,str,0);
                            access[tmp_index] = false;
                        }
                        break;
            case  2 :   SolArr[tmp_index] = fac->produce(tmp_index,__col,params);
                        if(SolArr[tmp_index]!=NULL) {
                            (*str) << SolArr[tmp_index]->toList().c_str();
                        	WxListBox1->InsertItems(1,str,0);
                            access[tmp_index] = false;
                        }
                        break;
            case  3 :   SolArr[tmp_index] = fac->produce(tmp_index,__col,params);
                        if(SolArr[tmp_index]!=NULL) {
                            (*str) << SolArr[tmp_index]->toList().c_str();
                        	WxListBox1->InsertItems(1,str,0);
                            access[tmp_index] = false;
                        }
                        break;
            case  4 :   SolArr[tmp_index] = fac->produce(tmp_index,__col,params);
                        if(SolArr[tmp_index]!=NULL) {
                            (*str) << SolArr[tmp_index]->toList().c_str();
                        	WxListBox1->InsertItems(1,str,0);
                            access[tmp_index] = false;
                        }
                        break;
            case  5 :   SolArr[tmp_index] = fac->produce(tmp_index,__col,params);
                        if(SolArr[tmp_index]!=NULL) {
                            (*str) << SolArr[tmp_index]->toList().c_str();
                        	WxListBox1->InsertItems(1,str,0);
                            access[tmp_index] = false;
                        }
                        break;
            case  6 :   __col = RGBCol(params[1],params[2],params[3]);
                        break;
            case  7 :   while(params[1] != SolArr[tmpID]->getID()) tmpID++;
                        delete SolArr[tmpID];
                        access[tmpID] = true;
                        tmpID = 0;
                        stmp << params[1];
                        while(WxListBox1->GetString(tmpID)[0] != stmp[0]) tmpID++;
                        WxListBox1->Delete(tmpID);
                        break;
            case  8 :   tmpID = 0;
                        stmp << params[1];                        
                        while(WxListBox1->GetString(tmpID)[0] != stmp[0]) tmpID++;
                        MoveSolid(SolArr[(int)params[0]],params);
                        (*str) << SolArr[(int)(params[0])]->toList().c_str();
                        WxListBox1->SetString(tmpID,(*str));
                        break;
            case  9 :   tmpID = 0;
                        stmp << params[1];                        
                        while(WxListBox1->GetString(tmpID)[0] != stmp[0]) tmpID++;
                        RotateSolid(SolArr[(int)params[0]],params);
                        (*str) << SolArr[(int)(params[0])]->toList().c_str();
                        WxListBox1->SetString(tmpID,(*str));
                        break;
            default :   rest(WxEdit1->GetLineText(0).ToStdString());
                        break;   
        }        
           	
    	delete str;
    }
	delete [] params;
	delete ch;
	WxEdit1->Clear();
	WxEdit1->SetFocus();
}
