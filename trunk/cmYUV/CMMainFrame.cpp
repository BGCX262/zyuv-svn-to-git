/*
 * zYUV Project
 *
 * Author: Aiden<aiden.lee@chipsnmedia.com>
 * Creation Date: 10/13/2012
 */
#include <wx/filedlg.h>
#include "CMMainFrame.h"
#include "CMRenderer.h"
#include "Dialog/CMYuvPropertyDlg.h"
#include "resources/playbutton.xpm"
#include "resources/prevbutton.xpm"
#include "resources/nextbutton.xpm"
#include "resources/openbutton.xpm"

enum {
    ID_RENDERER = 102,
    ID_SLIDER, 
    ID_OPEN,
    ID_PREV,
    ID_PLAY,
    ID_NEXT,
    ID_STOP,
};


BEGIN_EVENT_TABLE(CMMainFrame, wxFrame)
    EVT_MENU(wxID_OPEN,  CMMainFrame::OnOpen)
    EVT_MENU(wxID_ABOUT, CMMainFrame::OnAbout)
    EVT_MENU(wxID_EXIT,  CMMainFrame::OnQuit)
    EVT_BUTTON(ID_OPEN,  CMMainFrame::OnOpen)
    
END_EVENT_TABLE()

CMMainFrame::CMMainFrame(
    const wxString& title
    ) : wxFrame(NULL, wxID_ANY, title)
{
    wxMenuBar* menuBar = new wxMenuBar();

    wxMenu* menu = new wxMenu();
    menu->Append(wxID_OPEN, wxT("&Open\tAlt-O"), wxT("open yuv file"));
    menu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("exit program"));
    menuBar->Append(menu, wxT("&File"));

    menu = new wxMenu();
    menu->Append(wxID_ABOUT, wxT("&About"), wxT("about this program"));
    menuBar->Append(menu, wxT("&Help"));

    this->SetMenuBar(menuBar);

    wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(vBoxSizer);
    
    m_renderer = new CMRenderer(this);
    vBoxSizer->Add(m_renderer, 1, wxEXPAND);

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    vBoxSizer->Add(panel, 0, wxEXPAND|wxALIGN_BOTTOM);

    wxBoxSizer* vControlBox = new wxBoxSizer(wxVERTICAL);
    panel->SetSizer(vControlBox);

    wxSlider* slider = new wxSlider(panel, ID_SLIDER, 50, 1, 100);
    vControlBox->Add(slider, 0, wxEXPAND, 0);

    wxBoxSizer* hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    vControlBox->Add(hBoxSizer, 0, wxALIGN_CENTER, 0);

    wxBitmapButton* openButton = new wxBitmapButton(panel, ID_OPEN, wxBitmap(openbutton));
    hBoxSizer->Add(openButton, 0, wxALIGN_CENTER, 0);

    wxBitmapButton* prevButton = new wxBitmapButton(panel, ID_PREV, wxBitmap(prevbutton));
    hBoxSizer->Add(prevButton, 0, wxALIGN_CENTER_HORIZONTAL);

    wxBitmapButton* playButton = new wxBitmapButton(panel, ID_PLAY, wxBitmap(playbutton));
    hBoxSizer->Add(playButton, 0, wxALIGN_CENTER_HORIZONTAL);

    wxBitmapButton* nextButton = new wxBitmapButton(panel, ID_NEXT, wxBitmap(nextbutton));
    hBoxSizer->Add(nextButton, 0, wxALIGN_CENTER_HORIZONTAL);

#if 0
    // Load background image
    wxImage bgImage;
    if (bgImage.LoadFile(_T("./background.jpg"))) {
        m_bmp      = wxBitmap(bgImage);
        int width  = m_bmp.GetWidth();
        int height = m_bmp.GetHeight();
        this->SetClientSize(width, height);
    }

#endif
    Layout();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Center();
}


CMMainFrame::~CMMainFrame()
{
}


void
CMMainFrame::OnOpen(
    wxCommandEvent& event
    )
{
    wxFileDialog fileOpenDialg(this->GetParent(), wxT("Choose yuv file"), wxT("."), wxEmptyString, wxT("YUV files (*.yuv)|*.yuv|All files (*)|*"), wxOPEN);

    if (fileOpenDialg.ShowModal() == wxID_OK) {
        wxString path = fileOpenDialg.GetPath();
        int filterIndex = fileOpenDialg.GetFilterIndex();

        CMYuvPropertyDlg* dlg = new CMYuvPropertyDlg(NULL);
        if (dlg->ShowModal() == wxID_OK) {
            CMImageFormat format = dlg->GetImageFormat();
            if (format == CM_IMG_FMT_YUV_PLANAR) {
                int w = dlg->GetWidth();
                int h = dlg->GetHeight();
                CMYUVImage* image = new CMYUVImage(path, dlg->GetYUVFormat(), w, h);
                m_renderer->SetImage(image);
            } else {
                wxMessageBox(_T("Not supported"));
            }
        }
        delete dlg;
    }
}

void 
CMMainFrame::OnAbout(
    wxCommandEvent& event
    )
{
}

void
CMMainFrame::OnQuit(
    wxCommandEvent& event
    )
{
    this->Close();
}