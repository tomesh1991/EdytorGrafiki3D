//---------------------------------------------------------------------------
//
// Name:        EdytorApp.h
// Author:      Mateusz "Mefioo" Knapczyk
// Created:     2013-01-19 11:44:29
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __EDYTORFRMApp_h__
#define __EDYTORFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class EdytorFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
