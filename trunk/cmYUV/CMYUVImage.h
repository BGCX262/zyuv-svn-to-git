#ifndef __CMYUVIMAGE_H__
#define __CMYUVIMAGE_H__

#include <wx/wx.h>
#include <wx/file.h>

#include "CMImage.h"

class CMYUVImage : public wxObject
{
public:
    /* Constructor */
    CMYUVImage(void);
    CMYUVImage(wxString& path, CMYUVFormat format, int width, int height);

    ~CMYUVImage(void);

    /* Access methods */
    wxImage* GetImage();
    int GetWidth() { return m_width; }
    int GetHeight() { return m_height; }
    int GetNumFrames() { return m_numFrames; }

private:
    int m_width;
    int m_height;
    int m_frameSize;
    int m_numFrames;
    CMYUVFormat m_format;
    wxFile* m_stream;
};

#endif /* __CMYUVIMAGE_H__ */
