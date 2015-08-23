#include "CMYUVCanvas.h"

IMPLEMENT_CLASS(CMYUVCanvas, wxWindow)

BEGIN_EVENT_TABLE(CMYUVCanvas, wxWindow)
    EVT_PAINT(CMYUVCanvas::OnPaint)
END_EVENT_TABLE()

CMYUVCanvas::CMYUVCanvas(
    wxFrame* parent, 
    const wxString& path, 
    int width, 
    int height, 
    CMYUVFormat format
    ) : wxWindow(parent, wxID_ANY)
{
    m_numOfFrames = 0;
}

CMYUVCanvas::~CMYUVCanvas()
{

}

void CMYUVCanvas::OnPaint(wxPaintEvent& event)
{

}

bool CMYUVCanvas::Play()
{
    return true;
}

bool CMYUVCanvas::Stop()
{
    return true;
}

bool CMYUVCanvas::GoToNextFrame()
{
    return true;
}

bool CMYUVCanvas::GoToPrevFrame()
{
    return true;
}