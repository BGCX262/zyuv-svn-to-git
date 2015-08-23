/*
 *
 */
#ifndef __CM_IMAGE_FRAME_H__
#define __CM_IMAGE_FRAME_H__

#include <wx/wx.h>
#include "CMImage.h"

class CMYUVCanvas : public wxWindow
{
    DECLARE_CLASS(CMYUVCanvas)
    DECLARE_EVENT_TABLE()

public:
    CMYUVCanvas(wxFrame* parent, const wxString& path, int width, int height, CMYUVFormat format);
    virtual ~CMYUVCanvas();

    void OnPaint(wxPaintEvent& event);
    
    int GetNumOfFrames() {
        return m_numOfFrames;
    }
    
    /* playback methods */
    bool Play();
    bool Stop();
    bool GoToNextFrame();
    bool GoToPrevFrame();

private:
    wxBitmap m_image;
    int      m_numOfFrames;
};


#endif /* __CM_IMAGE_FRAME_H__ */