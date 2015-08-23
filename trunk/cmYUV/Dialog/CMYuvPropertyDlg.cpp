///-----------------------------------------------------------------
///
/// @file      CMYuvPropertyDlg.cpp
/// @author    zstein
/// Created:   2012-11-11 ¿ÀÈÄ 6:35:34
/// @section   DESCRIPTION
///            CMYuvPropertyDlg class implementation
///
///------------------------------------------------------------------

#include "CMYuvPropertyDlg.h"

// IDs for controls
enum {
    ID_PRESET = 2000,
    ID_WIDTH,
    ID_HEIGHT,
    ID_FORMAT,
    ID_SAMPLING
};

#define LABEL_SIZE wxSize(50, 20)

struct _SizePreset_struct {
    wxString name;
    int      width;
    int      height;
} s_sizePreset[] = {
    { _T("Custom"),  320,  240  },
    { _T("QCIF"),    176,  144  },
    { _T("CIF"),     352,  288  },
    { _T("Full HD"), 1920, 1080 }
};


//----------------------------------------------------------------------------
// CMYuvPropertyDlg
//----------------------------------------------------------------------------
////Event Table Start
BEGIN_EVENT_TABLE(CMYuvPropertyDlg,wxDialog)
	EVT_CLOSE(CMYuvPropertyDlg::OnClose)

	EVT_COMBOBOX(ID_PRESET,CMYuvPropertyDlg::OnPresetSelected)
END_EVENT_TABLE()


CMYuvPropertyDlg::CMYuvPropertyDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

CMYuvPropertyDlg::~CMYuvPropertyDlg()
{
} 

void CMYuvPropertyDlg::CreateGUIControls()
{
	wxBoxSizer*       hBoxSizer;
	wxBoxSizer*       vBoxSizer;
	wxStaticBoxSizer* staticBoxSizer;
	wxStaticText*     staticText;	
    wxString          szSize;

	// Main box sizer 
	vBoxSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(vBoxSizer);

	// wxStaticBoxSizer for framesize
	staticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("Framesize"));
	vBoxSizer->Add(staticBoxSizer, 0, wxALL, 5);

	// Add preset controls: static text control and combo box control
	hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	staticBoxSizer->Add(hBoxSizer, 0, wxEXPAND);
	staticText = new wxStaticText(this, wxID_ANY, _T("Preset"), wxDefaultPosition, LABEL_SIZE);
    hBoxSizer->Add(staticText, 0, wxALIGN_LEFT|wxALL, 4);
    wxArrayString presetChoice;
    int count = sizeof(s_sizePreset) / sizeof(struct _SizePreset_struct);
    for (int i=0; i<count; i++) {
        presetChoice.Add(s_sizePreset[i].name);
    }
    wxComboBox* comboPreset = new wxComboBox(
        this, ID_PRESET, wxEmptyString, wxDefaultPosition, wxSize(100, 22),
        presetChoice, wxCB_READONLY, wxDefaultValidator, _T("preset"));
    comboPreset->SetSelection(0);
    hBoxSizer->Add(comboPreset, 0, wxALIGN_RIGHT|wxALL, 4);

    m_width  = s_sizePreset[0].width;
    m_height = s_sizePreset[0].height;

    // Add width control
    hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    staticBoxSizer->Add(hBoxSizer);
    staticText = new wxStaticText(this, wxID_ANY, _T("Width:"), wxDefaultPosition, LABEL_SIZE);
    hBoxSizer->Add(staticText, 0, wxALIGN_LEFT|wxALL, 4);
    wxTextCtrl* editWidth = new wxTextCtrl(this, ID_WIDTH, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC));
    hBoxSizer->Add(editWidth, 0, wxALIGN_RIGHT|wxALL, 4);
    szSize.sprintf(_T("%d"), m_width);
    editWidth->SetValue(szSize);

    // Add height control
    hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    staticBoxSizer->Add(hBoxSizer);
    staticText = new wxStaticText(this, wxID_ANY, _T("Height:"), wxDefaultPosition, LABEL_SIZE);
    hBoxSizer->Add(staticText, 0, wxALIGN_LEFT|wxALL, 4);
    wxTextCtrl* editHeight = new wxTextCtrl(this, ID_HEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxTextValidator(wxFILTER_NUMERIC));
    hBoxSizer->Add(editHeight, 0, wxALIGN_RIGHT|wxALL, 4);
    szSize.sprintf(_T("%d"), m_height);
    editHeight->SetValue(szSize);

    // Add format
    staticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _T("format"));
    vBoxSizer->Add(staticBoxSizer, 0, wxALL, 5);

    hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    staticBoxSizer->Add(hBoxSizer);
    staticText = new wxStaticText(this, wxID_ANY, _T("Format"), wxDefaultPosition, LABEL_SIZE);
    hBoxSizer->Add(staticText, 0, wxALIGN_LEFT|wxALL, 4);

    wxArrayString listFormat;
    listFormat.Add(_T("YUV"));
    wxComboBox* comboFormat = new wxComboBox(
        this, ID_FORMAT, wxEmptyString, wxDefaultPosition, wxSize(100, 22),
        listFormat, wxCB_READONLY, wxDefaultValidator, _T("yuv"));
    comboFormat->SetSelection(0);
    hBoxSizer->Add(comboFormat, 0, wxALIGN_RIGHT|wxALL, 4);

    /* Sampling */
    hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    staticBoxSizer->Add(hBoxSizer);
    staticText = new wxStaticText(this, wxID_ANY, _T("Sampling"), wxDefaultPosition, LABEL_SIZE);
    hBoxSizer->Add(staticText, 0, wxALIGN_LEFT|wxALL, 4);

    wxArrayString listSampling;
    listSampling.Add(_T("YUV400"));
    listSampling.Add(_T("YUV420"));
    listSampling.Add(_T("YUV422"));
    listSampling.Add(_T("YUV444"));
    wxComboBox* comboSampling = new wxComboBox(
        this, ID_SAMPLING, wxEmptyString, wxDefaultPosition, wxSize(100, 22),
        listSampling, wxCB_READONLY, wxDefaultValidator, _T("sampling"));
    comboSampling->SetSelection(1); /* default YUV420 */
    hBoxSizer->Add(comboSampling, 0, wxALIGN_RIGHT|wxALL, 4);

    // OK button and cancel button
    wxStdDialogButtonSizer* buttonSizer = new wxStdDialogButtonSizer();
    vBoxSizer->Add(buttonSizer, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxButton* okButton = new wxButton(this, wxID_OK, _T("OK"));
    buttonSizer->SetAffirmativeButton(okButton);
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, _T("Cancel"));
    buttonSizer->SetCancelButton(cancelButton);
    buttonSizer->Realize();

	SetTitle(_("zyuv"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
}

void CMYuvPropertyDlg::OnClose(wxCloseEvent& /*event*/)
{
	Destroy();
}

// No description
void CMYuvPropertyDlg::OnPresetSelected(wxCommandEvent& event)
{
	/* TODO (#1#): Implement CMYuvPropertyDlg::OnPresetSelected() */
    wxComboBox* comboBox = (wxComboBox*)FindWindow(ID_PRESET);
    int selectedIdx      = comboBox->GetSelection();
    wxString string;

    m_width  = s_sizePreset[selectedIdx].width;
    m_height = s_sizePreset[selectedIdx].height;

    wxTextCtrl* edit = (wxTextCtrl*)FindWindow(ID_WIDTH);
    string.sprintf(_T("%d"), m_width);
    edit->SetValue(string);

    edit = (wxTextCtrl*)FindWindow(ID_HEIGHT);
    string.sprintf(_T("%d"), m_height);
    edit->SetValue(string);
}

/**
 * 
 */
bool
CMYuvPropertyDlg::TransferDataFromWindow()
{
    wxComboBox* comboBox;
    wxTextCtrl* edit;

    comboBox = (wxComboBox*)FindWindow(ID_FORMAT);
    m_imageFormat = (CMImageFormat)comboBox->GetSelection();

    comboBox = (wxComboBox*)FindWindow(ID_SAMPLING);
    m_yuvFormat = (CMYUVFormat)comboBox->GetSelection();

    edit = (wxTextCtrl*)FindWindow(ID_WIDTH);
    edit->GetValue().ToLong((long*)&m_width);

    edit = (wxTextCtrl*)FindWindow(ID_HEIGHT);
    edit->GetValue().ToLong((long*)&m_height);

    return true;
}