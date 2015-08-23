#ifndef __CM_MAIN_FRAME_H__
#define __CM_MAIN_FRAME_H__

#include "wx/wx.h"
#include "CMYUVImage.h"
#include "CMRenderer.h"

class CMMainFrame : public wxFrame
{
public:
    CMMainFrame(const wxString& title);
    ~CMMainFrame();

    // Menu Event Handlers
    // File
    void OnOpen(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);

    // Help
    void OnAbout(wxCommandEvent& event);

private:
    CMRenderer* m_renderer;

    DECLARE_EVENT_TABLE()
};

#endif /* __CM_MAIN_FRAME_H__ */
