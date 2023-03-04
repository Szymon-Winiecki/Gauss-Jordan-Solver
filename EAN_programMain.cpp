/***************************************************************
 * Name:      EAN_programMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Szymon Winiecki ()
 * Created:   2021-05-28
 * Copyright: Szymon Winiecki ()
 * License:
 **************************************************************/

#include <iostream>
#include "EAN_programMain.h"
#include <wx/msgdlg.h>
#include <wx/textfile.h>

#include <exception>
#include <fstream>

//(*InternalHeaders(EAN_programFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(EAN_programFrame)
const long EAN_programFrame::ID_STATICTEXT1 = wxNewId();
const long EAN_programFrame::ID_BUTTON2 = wxNewId();
const long EAN_programFrame::ID_TEXTCTRL2 = wxNewId();
const long EAN_programFrame::ID_BUTTON3 = wxNewId();
const long EAN_programFrame::ID_BUTTON4 = wxNewId();
const long EAN_programFrame::ID_CHECKBOX1 = wxNewId();
const long EAN_programFrame::ID_RADIOBOX1 = wxNewId();
const long EAN_programFrame::ID_CHECKBOX2 = wxNewId();
const long EAN_programFrame::ID_TEXTCTRL1 = wxNewId();
const long EAN_programFrame::ID_PANEL1 = wxNewId();
const long EAN_programFrame::idMenuQuit = wxNewId();
const long EAN_programFrame::ID_inputFormatHelp = wxNewId();
const long EAN_programFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(EAN_programFrame,wxFrame)
    //(*EventTable(EAN_programFrame)
    //*)
END_EVENT_TABLE()

EAN_programFrame::EAN_programFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EAN_programFrame)
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;

    Create(parent, wxID_ANY, _("Gauss-Jordan"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(858,688));
    MainPanel = new wxPanel(this, ID_PANEL1, wxPoint(0,120), wxSize(856,629), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StaticText1 = new wxStaticText(MainPanel, ID_STATICTEXT1, _("Solve the sytem of linear equations with Gauss-Jordan method\n"), wxPoint(128,32), wxSize(608,48), wxALIGN_CENTRE, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    solve_button = new wxButton(MainPanel, ID_BUTTON2, _("solve"), wxPoint(272,368), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    matrix_text = new wxTextCtrl(MainPanel, ID_TEXTCTRL2, wxEmptyString, wxPoint(40,96), wxSize(544,256), wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    wxFont matrix_textFont(11,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Ubuntu Mono"),wxFONTENCODING_DEFAULT);
    matrix_text->SetFont(matrix_textFont);
    chooseInputFile_button = new wxButton(MainPanel, ID_BUTTON3, _("file input"), wxPoint(608,272), wxSize(104,34), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    chooseOutputFile_button = new wxButton(MainPanel, ID_BUTTON4, _("output file"), wxPoint(608,320), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    formatInputCheckbox = new wxCheckBox(MainPanel, ID_CHECKBOX1, _("display formatted input"), wxPoint(616,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    formatInputCheckbox->SetValue(false);
    wxString __wxRadioBoxChoices_1[3] =
    {
    	_("floating point"),
    	_("interval with number input"),
    	_("interval with interval input")
    };
    arithmeticSelection = new wxRadioBox(MainPanel, ID_RADIOBOX1, _("arithmetic"), wxPoint(616,96), wxSize(232,96), 3, __wxRadioBoxChoices_1, 3, 0, wxDefaultValidator, _T("ID_RADIOBOX1"));
    outputToFile_checkbox = new wxCheckBox(MainPanel, ID_CHECKBOX2, _("output to file"), wxPoint(720,328), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    outputToFile_checkbox->SetValue(false);
    result_text = new wxTextCtrl(MainPanel, ID_TEXTCTRL1, wxEmptyString, wxPoint(40,416), wxSize(792,208), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    result_text->SetBackgroundColour(wxColour(230,230,230));
    wxFont result_textFont(11,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Ubuntu Mono"),wxFONTENCODING_DEFAULT);
    result_text->SetFont(result_textFont);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, ID_inputFormatHelp, _("input format"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("&help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    InputFileDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    OutputFileDialog = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EAN_programFrame::Onsolve_buttonClick);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&EAN_programFrame::Onmatrix_textText);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EAN_programFrame::OnchooseFile_buttonClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EAN_programFrame::OnchooseOutputFile_buttonClick);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&EAN_programFrame::OnformatInputCheckboxClick);
    Connect(ID_RADIOBOX1,wxEVT_COMMAND_RADIOBOX_SELECTED,(wxObjectEventFunction)&EAN_programFrame::OnarithmeticSelectionSelect);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&EAN_programFrame::OnoutputToFile_checkboxClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EAN_programFrame::OnQuit);
    //*)
    Connect(ID_inputFormatHelp,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EAN_programFrame::OnAbout);
}

EAN_programFrame::~EAN_programFrame()
{
    //(*Destroy(EAN_programFrame)
    //*)
}

void EAN_programFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EAN_programFrame::OnAbout(wxCommandEvent& event)
{
    //wxString msg = wxbuildinfo(long_f);
    wxString help = _("Separate rows with a new line and columns with spaces");
    wxMessageBox(help, _("Input format"));
}

void EAN_programFrame::updateInput(){
    if(formatInput){
        matrix_text->SetEditable(false);
        matrix_text->SetBackgroundColour(wxColour(230,230,230));
        matrix_text->SetValue(_(readInput()));

    }
    else{
        matrix_text->SetEditable(true);
        matrix_text->SetBackgroundColour(wxColour(255,255,255));
        matrix_text->SetValue(_(userInput));
    }
}

void EAN_programFrame::updateOutput(){

}

std::string EAN_programFrame::readInput(){
    try{
        if(useIntervalArithmetic){
            originalIntervalMatrix = NumericalCore::Matrix<interval_arithmetic::Interval<long double>>(userInput, intervalInput);
            return originalIntervalMatrix.toString();
        }
        else{
            originalFloatingPointMatrix = NumericalCore::Matrix<long double>(userInput);
            return originalFloatingPointMatrix.toString();
        }
    }
    catch(const std::invalid_argument& exception){
        return exception.what();
    }
    catch(const std::out_of_range& exception){
        return exception.what();
    }
    catch(...){
        return "Something went wrong, try again";
    }
}

std::string EAN_programFrame::getResult(){
    if(useIntervalArithmetic){
        intervalSystem = NumericalCore::LinearEquationsSystem<interval_arithmetic::Interval<long double>>(originalIntervalMatrix);
        return intervalSystem.getFormattedResult();
    }
    else{
        floatingPointSystem = NumericalCore::LinearEquationsSystem<long double>(originalFloatingPointMatrix);
        return floatingPointSystem.getFormattedResult();
    }
}

std::string EAN_programFrame::solveSystem(){
    try{
        if(useIntervalArithmetic){
            originalIntervalMatrix = NumericalCore::Matrix<interval_arithmetic::Interval<long double>>(userInput, intervalInput);
            intervalSystem = NumericalCore::LinearEquationsSystem<interval_arithmetic::Interval<long double>>(originalIntervalMatrix);
            return intervalSystem.getFormattedResult();
        }
        else{
            originalFloatingPointMatrix = NumericalCore::Matrix<long double>(userInput);
            floatingPointSystem = NumericalCore::LinearEquationsSystem<long double>(originalFloatingPointMatrix);
            return floatingPointSystem.getFormattedResult();
        }
    }
    catch(const std::invalid_argument& exception){
        return exception.what();
    }
    catch(const std::out_of_range& exception){
        return exception.what();
    }
    catch(...){
        return "Something went wrong, try again";
    }
}

void EAN_programFrame::Onsolve_buttonClick(wxCommandEvent& event)
{
    if(!formatInput){
        userInput = matrix_text->GetValue().ToStdString();
    }
    std::string result = solveSystem();

    result_text->SetValue(_(result));

    if(outputToFile_checkbox->GetValue()){
        std::ofstream outputFile;
        outputFile.open(outputFilePath.ToStdString());
        outputFile << result;
        outputFile.close();
        outputToFile_checkbox->SetValue(false);
    }

    updateInput();
}

void EAN_programFrame::Onmatrix_textText(wxCommandEvent& event)
{

}

void EAN_programFrame::OnoutputToFile_checkboxClick(wxCommandEvent& event){
}

void EAN_programFrame::OnchooseFile_buttonClick(wxCommandEvent& event)
{
    int status = InputFileDialog->ShowModal();
    if(status != wxID_OK){
        return;
    }

    wxTextFile file;
    file.Open(InputFileDialog->GetPath());
    wxString fileContent;
    for(size_t i = 0; i < file.GetLineCount(); ++i){
        fileContent << file.GetLine(i) << "\n";
    }
    file.Write();
    file.Close();
    matrix_text->SetValue(fileContent);

}

void EAN_programFrame::OnchooseOutputFile_buttonClick(wxCommandEvent& event)
{
    int status = OutputFileDialog->ShowModal();
    if(status != wxID_OK){
        return;
    }
    outputFilePath = OutputFileDialog->GetPath();
    outputToFile_checkbox->SetValue(true);
}

void EAN_programFrame::OnformatInputCheckboxClick(wxCommandEvent& event)
{
    if(!formatInput){
        userInput = matrix_text->GetValue().ToStdString();
    }

    formatInput = formatInputCheckbox->GetValue();
    updateInput();
}

void EAN_programFrame::OnarithmeticSelectionSelect(wxCommandEvent& event)
{
    if(!formatInput){
        userInput = matrix_text->GetValue().ToStdString();
    }

    if(arithmeticSelection->GetSelection() == 1){
        useIntervalArithmetic = true;
        intervalInput = false;
    }
    else if(arithmeticSelection->GetSelection() == 2){
        useIntervalArithmetic = true;
        intervalInput = true;
    }
    else{
        useIntervalArithmetic = false;
        intervalInput = false;
    }
    updateInput();
}
