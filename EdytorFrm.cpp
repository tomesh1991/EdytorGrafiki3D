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
#include "String_Splitter.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

double d=-2.0;

Matrix macierz;
Matrix macierzRotacjaX;
Matrix macierzRotacjaY;
Matrix macierzRotacjaZ;
Matrix macierzSkalowanie;
Matrix macierzTranslacjaX;
Matrix macierzTranslacjaY;
Matrix macierzTranslacjaZ;

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
	
	EVT_UPDATE_UI(ID_WXPANEL,EdytorFrm::WxPanelUpdateUI)

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

	WxPanel2 = new wxPanel(this, ID_WXPANEL2, wxPoint(482, 22), wxSize(300, 300));
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
    sol->move(params);
}

void EdytorFrm::RotateSolid(Solid* sol, double* params) {
    sol->rotate(params);
}

void EdytorFrm::SaveSolid(string file_name) {
    ofstream file(file_name.c_str()); //otwieramy plik
    for(unsigned int i = 0; i < 100; ++i){
        if(access[i] != true){
            file << SolArr[i]->toList() << std::endl; //wstawiamy reprezentacje stringowa kazdego solida do pliku
            ++i;
        }
    }//utworzony plik jest de facto skryptem z poleceniami programu, ktore zostana zinterpretowane podczas jego wczytywania 
    file.close(); //zamykamy plik
}

void EdytorFrm::LoadSolid(string file_name) {
    ifstream file(file_name.c_str()); //otwieramy plik
    std::vector<string>* v;
    std::string str;
    for(unsigned int i = 0; i < 100; ++i){
        if(SolArr[i] != NULL){
            delete SolArr[i];
            access[i] = true;
        }
    }
    unsigned int array_index = 0; 
    //oczyszczamy tablicy solidow dla pewnosci
    WxListBox1->Clear();
    
    if(file){
        while(getline(file, str)){
            int solid_id;
            int id;
            wxString *s = new wxString();
            for(unsigned int i = 0; i < str.length(); ++i){
                if(str[i] == '(' && str[i] ==')'){
                    str.erase(str.begin() + i); //oczyszczamy stringa z nawiasów
                }
                if(str[i] == ' '){
                    str[i] = ','; //zamieniamy spacje na przecinki (jednolity separator danych)
                }
            }
            v = string_splitter(str,","); //dzielimy przetworzonego stringa z komenda programu na poszczegolne skladowe
            
            if(v->at(1).compare("line")){
                solid_id = 1; //okreslamy typ zadanej bryly
                id = strtod(v->at(0).c_str(),NULL);  //wyciagamy nr ID bryly
                double param[7];
                param[0] = solid_id;
                
                for(unsigned int i = 1; i < 7; ++i){
                    param[i] = strtod(v->at(i+1).c_str(),NULL);
                }
                //tworzymy i wypelniamy wartosciami tablice zawierajaca parametry tworzonej bryly
                SolArr[array_index] = fac->produce(id,__col,param);
                access[array_index] = false;
                //wstawiamy utworzona bryle w kontenerze i ustawiamy flage dostepnosci komorki na zajeta
                (*s) << SolArr[array_index]->toList().c_str();
                WxListBox1->InsertItems(1,s,0);
                //uzupelniamy liste aktualnie wyswietlanych figur o aktualnie dodana
                ++array_index;
                
            }else if(v->at(1).compare("box")){
                solid_id = 2;
                id = strtod(v->at(0).c_str(),NULL);
                double param[7];
                param[0] = solid_id;
                
                for(unsigned int i = 1; i < 7; ++i){
                    param[i] = strtod(v->at(i+1).c_str(),NULL);
                }
                
                SolArr[array_index] = fac->produce(id,__col,param);
                access[array_index] = false;
                (*s) << SolArr[array_index]->toList().c_str();
                WxListBox1->InsertItems(1,s,0);
                ++array_index;
                
            }else if(v->at(1).compare("sphere")){
                solid_id = 3;
                id = strtod(v->at(0).c_str(),NULL);
                double param[7];
                param[0] = solid_id;
                
                for(unsigned int i = 1; i < 7; ++i){
                    param[i] = strtod(v->at(i+1).c_str(),NULL);
                }
                
                SolArr[array_index] = fac->produce(id,__col,param);
                access[array_index] = false;
                (*s) << SolArr[array_index]->toList().c_str();
                WxListBox1->InsertItems(1,s,0);
                ++array_index;
                
            }else if(v->at(1).compare("cone")){
                solid_id = 4;
                id = strtod(v->at(0).c_str(),NULL);
                double param[9];
                param[0] = solid_id;
                
                for(unsigned int i = 1; i < 9; ++i){
                    param[i] = strtod(v->at(i+1).c_str(),NULL);
                }
                
                SolArr[array_index] = fac->produce(id,__col,param);
                access[array_index] = false;
                (*s) << SolArr[array_index]->toList().c_str();
                WxListBox1->InsertItems(1,s,0);
                ++array_index;
                
            }else if(v->at(1).compare("cylinder")){
                solid_id = 5;
                id = strtod(v->at(0).c_str(),NULL);
                double param[8];
                param[0] = solid_id;
                
                for(unsigned int i = 1; i < 8; ++i){
                    param[i] = strtod(v->at(i+1).c_str(),NULL);
                }
                
                SolArr[array_index] = fac->produce(id,__col,param);
                access[array_index] = false;
                (*s) << SolArr[array_index]->toList().c_str();
                WxListBox1->InsertItems(1,s,0);
                ++array_index;
            }else{
                solid_id = 0;
            }
            delete v; 
            delete s;
        }//interpreter polecen zapisanych w pliku
    }
    file.close(); //zamykamy plik
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
	Repaint();
}

void EdytorFrm::Repaint() {
 wxClientDC dc1(WxPanel1);
 wxClientDC dc2(WxPanel2);
 wxClientDC dc3(WxPanel3);
 wxClientDC dc4(WxPanel4);
 
 int w1, h1, w2, h2, w3, h3, w4, h4;
 int _w1, _h1, _w2, _h2, _w3, _h3, _w4, _h4;
 int r, g, b;
 
 WxPanel1->GetSize(&w1,&h1);
 WxPanel2->GetSize(&w2,&h2);
 WxPanel3->GetSize(&w3,&h3);
 WxPanel4->GetSize(&w4,&h4);
  
 wxBufferedDC bdc1(&dc1, wxSize(w1,h1));
 wxBufferedDC bdc2(&dc2, wxSize(w2,h2));
 wxBufferedDC bdc3(&dc3, wxSize(w3,h3));
 wxBufferedDC bdc4(&dc4, wxSize(w4,h4));
 
 _w1=w1/2.; _h1=h1/2.;
 _w2=w2/2.; _h2=h2/2.;
 _w3=w3/2.; _h3=h3/2.;
 _w4=w4/2.; _h4=h4/2.;
 
 bdc1.SetBackground(wxBrush(RGB(255,255,255)));
 bdc1.Clear(); 
 bdc2.SetBackground(wxBrush(RGB(255,255,255)));
 bdc2.Clear(); 
 bdc3.SetBackground(wxBrush(RGB(255,255,255)));
 bdc3.Clear(); 
 bdc4.SetBackground(wxBrush(RGB(255,255,255)));
 bdc4.Clear();
 
 Vector* cvVector;
//*****************szel¹gowe macierze***********************************8
  double x0,x1,x2,y0,y1,y2,z1,z2;
  for(int i = 0;i<=3;i++)
    for(int j = 0;j<=3;j++)
        macierz.data[i][j]=0;
        
    macierz.data[0][0]=(1.0*_w1)/100;
    macierz.data[1][1]=(1.0*_h1)/100;
    macierz.data[2][2]=1.0;
   
/// Rotacja X
       
    macierzRotacjaX.data[0][0]=1.0;
    macierzRotacjaX.data[1][2]=sin((0*2*3.14)/360);
    macierzRotacjaX.data[2][1]=-sin((0*2*3.14)/360);  
    macierzRotacjaX.data[1][1]=1.0*cos((0*2*3.14)/360);
    macierzRotacjaX.data[2][2]=1.0*cos((0*2*3.14)/360);    
/// Rotacja Y 
    macierzRotacjaY.data[1][1]=1.0;
    macierzRotacjaY.data[0][2]=-sin((0*2*3.14)/360);
    macierzRotacjaY.data[2][0]=sin((0*2*3.14)/360);  
    macierzRotacjaY.data[0][0]=1.0*cos((0*2*3.14)/360);
    macierzRotacjaY.data[2][2]=1.0*cos((0*2*3.14)/360); 
    
/// Rotacja Z
    macierzRotacjaZ.data[0][0]=1.0*cos((0*2*3.14)/360);
    macierzRotacjaZ.data[0][1]=sin((0*2*3.14)/360);
    macierzRotacjaZ.data[1][0]=-sin((0*2*3.14)/360);  
    macierzRotacjaZ.data[1][1]=1.0*cos((0*2*3.14)/360);
    macierzRotacjaZ.data[2][2]=1.0;
/// Skalowanie
    
    macierzSkalowanie.data[0][0]=1*99;
    macierzSkalowanie.data[1][1]=1*99;
    macierzSkalowanie.data[2][2]=1*99;
    
    /// Translacja
    macierzTranslacjaX.data[0][0]=1.0;
    macierzTranslacjaX.data[1][1]=1.0;
    macierzTranslacjaX.data[2][2]=1.0;
    
    double x = macierzTranslacjaX.data[3][0]=1.0*50;
    double y = macierzTranslacjaX.data[3][1]=1.0*50;
    double z = macierzTranslacjaX.data[3][2]=-(1.0*50-120)/60;         

    macierz=macierz*macierzTranslacjaX*macierzRotacjaX*macierzRotacjaY*macierzRotacjaZ*macierzSkalowanie;  
//***************************************************
 bdc1.SetDeviceOrigin(_w1, _h1);
 bdc2.SetDeviceOrigin(_w2, _h2);
 bdc3.SetDeviceOrigin(_w3, _h3);
 bdc4.SetDeviceOrigin(_w4, _h4);
 
 for(int i = 0; i < 100 ;i++){
   if(!access[i])     
    for(int j = 0; j < SolArr[i]->getSize();j++){
        cvVector = SolArr[i]->getSingleVec(j);
        Coord cvBegin = cvVector->getBegin();
        Coord cvEnd = cvVector->getEnd(); 
        macierz*cvBegin;
        macierz*cvEnd;
        Vector* cvVector2 = new Vector();
        cvVector2->setBegin(cvBegin);
        cvVector2->setEnd(cvEnd);
        
        x0 = ((cvVector2->getBegin().get_x()+x)/z)-50; 
        y0 = ((-cvVector2->getBegin().get_y()-y)/z)+50;
        x1 = ((cvVector2->getEnd().get_x()+x)/z)-50;
        y1 = ((-cvVector2->getEnd().get_y()-y)/z)+50;
        
        r = cvVector->getColour().get_r();
        g = cvVector->getColour().get_g();
        b = cvVector->getColour().get_b();
        
        bdc1.SetPen(wxPen(RGB(r,g,b)));
        bdc1.DrawLine(x0,y0,x1,y1);
        
                
        bdc2.SetPen(wxPen(RGB(r,g,b)));
        bdc2.DrawLine(x0,y0,x1,y1);
        
                
        bdc3.SetPen(wxPen(RGB(r,g,b)));
        bdc3.DrawLine(x0,y0,x1,y1);
        
                
        bdc4.SetPen(wxPen(RGB(r,g,b)));
        bdc4.DrawLine(x0,y0,x1,y1);
        delete cvVector2;
    }           
 }
}

void EdytorFrm::WxPanelUpdateUI(wxUpdateUIEvent& event){
    Repaint();
}
