/***************************************************************
 * Name:      EAN_programMain.h
 * Purpose:   Defines Application Frame
 * Author:    Szymon Winiecki ()
 * Created:   2021-05-28
 * Copyright: Szymon Winiecki ()
 * License:
 **************************************************************/

#ifndef EAN_PROGRAMMAIN_H
#define EAN_PROGRAMMAIN_H

//(*Headers(EAN_programFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

#include "NumericalCore/Matrix.h"
#include "NumericalCore/LinearEquationsSystem.h"
#include "NumericalCore/Interval.h"


class EAN_programFrame: public wxFrame
{
    public:

        EAN_programFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~EAN_programFrame();

    private:

        //(*Handlers(EAN_programFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnHelloButtonClick(wxCommandEvent& event);
        void OnRichTextCtrl1Text(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnTextCtrl3Text(wxCommandEvent& event);
        void Onsolve_buttonClick(wxCommandEvent& event);
        void Onmatrix_textText(wxCommandEvent& event);
        void OnchooseFile_buttonClick(wxCommandEvent& event);
        void OnchooseOutputFile_buttonClick(wxCommandEvent& event);
        void OnformatInputCheckboxClick(wxCommandEvent& event);
        void OnarithmeticSelectionSelect(wxCommandEvent& event);
        void OnoutputToFile_checkboxClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(EAN_programFrame)
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON2;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_CHECKBOX1;
        static const long ID_RADIOBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long ID_inputFormatHelp;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(EAN_programFrame)
        wxButton* chooseInputFile_button;
        wxButton* chooseOutputFile_button;
        wxButton* solve_button;
        wxCheckBox* formatInputCheckbox;
        wxCheckBox* outputToFile_checkbox;
        wxFileDialog* InputFileDialog;
        wxFileDialog* OutputFileDialog;
        wxMenu* Menu2;
        wxMenuItem* MenuItem2;
        wxPanel* MainPanel;
        wxRadioBox* arithmeticSelection;
        wxStaticText* StaticText1;
        wxStatusBar* StatusBar1;
        wxTextCtrl* matrix_text;
        wxTextCtrl* result_text;
        //*)

        std::string solveSystem();
        std::string getResult();
        std::string readInput();
        void updateInput();
        void updateOutput();

        std::string userInput;
        std::string formattedInput;
        wxString outputFilePath;
        bool useIntervalArithmetic = false;
        bool intervalInput = false;
        bool formatInput = false;

        NumericalCore::Matrix<long double> originalFloatingPointMatrix;
        NumericalCore::Matrix<interval_arithmetic::Interval<long double>> originalIntervalMatrix;
        NumericalCore::LinearEquationsSystem<long double> floatingPointSystem;
        NumericalCore::LinearEquationsSystem<interval_arithmetic::Interval<long double>> intervalSystem;

        DECLARE_EVENT_TABLE()
};

#endif // EAN_PROGRAMMAIN_H
