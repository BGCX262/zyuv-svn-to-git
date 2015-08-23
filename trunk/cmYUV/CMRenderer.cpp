/*
 * zYUV Project
 *
 * CMRenderer.cpp 
 */

#include <wx/event.h>
#include <wx/utils.h>
#include "CMRenderer.h"

BEGIN_EVENT_TABLE(CMRenderer,wxWindow)
    EVT_PAINT(CMRenderer::OnPaint)
    EVT_SIZE(CMRenderer::OnSize)
    EVT_ERASE_BACKGROUND(CMRenderer::OnEraseBackground)
END_EVENT_TABLE()

CMRenderer::CMRenderer(
    wxWindow* parent
    ) : wxWindow(parent, wxID_ANY)
{
    this->SetSize(320, 240);
    m_image = NULL;
    m_bmp   = NULL;
}

CMRenderer::~CMRenderer(
    void
    )
{
    if (m_image) delete m_image;
    if (m_bmp)   delete m_bmp;
}

void
CMRenderer::OnPaint(
    wxPaintEvent& event
    )
{
    wxPaintDC dc(this);
    PrepareDC(dc);

    wxSize size = GetClientSize();
    wxBitmap bmp(size.x, size.y);
    wxMemoryDC memDC;

    /* fill background color */
    memDC.SelectObject(bmp);
    memDC.SetBackground(*wxBLACK_BRUSH);

    if (m_image && m_bmp) {
        int dstX = (size.x - m_image->GetWidth()) / 2;
        int dstY = (size.y - m_image->GetHeight()) / 2;

        if (m_bmp) memDC.DrawBitmap(*m_bmp, dstX, dstY);
    }

    dc.Blit(0, 0, size.x, size.y, &memDC, 0, 0);
}

/*
 * Resize event handler 
 */
void
CMRenderer::OnSize(
    wxSizeEvent& event
    )
{
    Refresh();
    event.Skip();
}


void
CMRenderer::SetImage(
    CMYUVImage* image
    )
{
    if (image == NULL) return;

    if (m_image != NULL) delete m_image;

    m_image = image;

    wxImage* wx_image = m_image->GetImage();
    int w = image->GetWidth();
    int h = image->GetHeight();

    wxSize clientSize = GetClientSize();
    if (w < clientSize.x) w = clientSize.x;
    if (h < clientSize.y) h = clientSize.y;


    if (m_bmp) delete m_bmp;
    m_bmp = new wxBitmap(*wx_image);

    delete wx_image;

    if (w == clientSize.x && h == clientSize.y) {
        Refresh();
    } else {
        /* SetClientSize() sends a paint event */
        SetClientSize(w, h);
    }
}

