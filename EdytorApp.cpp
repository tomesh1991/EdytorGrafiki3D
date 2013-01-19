//---------------------------------------------------------------------------
//
// Name:        EdytorApp.cpp
// Author:      Mateusz "Mefioo" Knapczyk
// Created:     2013-01-19 11:44:29
// Description: 
//
//---------------------------------------------------------------------------

#include "EdytorApp.h"
#include "EdytorFrm.h"

IMPLEMENT_APP(EdytorFrmApp)

bool EdytorFrmApp::OnInit()
{
    EdytorFrm* frame = new EdytorFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int EdytorFrmApp::OnExit()
{
	return 0;
}
