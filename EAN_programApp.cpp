/***************************************************************
 * Name:      EAN_programApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Szymon Winiecki ()
 * Created:   2021-05-28
 * Copyright: Szymon Winiecki ()
 * License:
 **************************************************************/

#include "EAN_programApp.h"

//(*AppHeaders
#include "EAN_programMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EAN_programApp);

bool EAN_programApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EAN_programFrame* Frame = new EAN_programFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
