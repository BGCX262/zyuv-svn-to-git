#include "CMYUVImage.h"


CMYUVImage::CMYUVImage(
    void
    )
{
}

CMYUVImage::CMYUVImage(
    wxString&   path, 
    CMYUVFormat format, 
    int         width, 
    int         height
    ) : m_width(width), m_height(height), m_format(format)
{
    m_stream = new wxFile(path.wx_str(), wxFile::read);
    if (m_stream->Error() == true) {
        delete m_stream;
        m_stream = NULL;
    }

    wxStructStat stat;
    wxStat(path.wx_str(), &stat);

    switch (m_format) {
    case CM_YUV_FMT_400: m_frameSize = m_width * m_height;  break;
    case CM_YUV_FMT_420: m_frameSize = m_width * m_height * 3/2; break;
    case CM_YUV_FMT_422: m_frameSize = m_width * m_height * 2;   break;
    case CM_YUV_FMT_444: m_frameSize = m_width * m_height * 3;   break;
    }

    m_numFrames = stat.st_size / m_frameSize;
}


CMYUVImage::~CMYUVImage(void)
{
    if (m_stream) delete m_stream;
}

wxImage*
CMYUVImage::GetImage(
    void
    )
{
    unsigned char* yuv = new unsigned char[m_frameSize];
    size_t nread = m_stream->Read(yuv, m_frameSize);
    if (nread == wxInvalidOffset) {
        return NULL;
    }

    CMRGB* rgb = CMImage::convertYUVtoRGB(yuv, m_width, m_height,  m_format);
    if (rgb == NULL) return NULL;
    delete [] yuv;

    wxImage* image = new wxImage(m_width, m_height, (unsigned char*)rgb);

    return image;
}