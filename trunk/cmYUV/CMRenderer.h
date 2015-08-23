/*
 * zYUV Project
 *
 * CMRenderer.h
 */

#ifndef __CM_RENDERER_H__
#define __CM_RENDERER_H__

#include <wx/wx.h>
#include "CMYUVImage.h"

class CMRenderer : public wxWindow {
    DECLARE_EVENT_TABLE()
public:
    CMRenderer(wxWindow* parent);
    ~CMRenderer(void);

    /* Access methods */
    void SetImage(CMYUVImage* image);

private:
    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnEraseBackground(wxEraseEvent& event) {}

private:
    CMYUVImage* m_image;
    wxBitmap*   m_bmp;
};

#endif /* __CM_RENDERER_H__ */