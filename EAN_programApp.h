/***************************************************************
 * Name:      EAN_programApp.h
 * Purpose:   Defines Application Class
 * Author:    Szymon Winiecki ()
 * Created:   2021-05-28
 * Copyright: Szymon Winiecki ()
 * License:
 **************************************************************/

#ifndef EAN_PROGRAMAPP_H
#define EAN_PROGRAMAPP_H

#include <wx/app.h>

class EAN_programApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // EAN_PROGRAMAPP_H
