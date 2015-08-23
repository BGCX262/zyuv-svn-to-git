#include "CMMainFrame.h"

#define PROGRAM_NAME            wxT("cmYUV")

class CMYUVApp : public wxApp
{
public:
    virtual bool OnInit();
};

DECLARE_APP(CMYUVApp)

IMPLEMENT_APP(CMYUVApp)

bool
CMYUVApp::OnInit()
{
    wxInitAllImageHandlers();

    CMMainFrame* frame = new CMMainFrame(PROGRAM_NAME);
    frame->Show();

    return true;
}