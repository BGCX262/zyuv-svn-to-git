#ifndef __CM_IMAGE_H__
#define __CM_IMAGE_H__

typedef enum {
    CM_IMG_FMT_YUV_PLANAR,
    CM_IMG_FMT_YUV_PACKED,
    CM_IMG_FMT_RGB,
} CMImageFormat;

#pragma pack(push, 1)
typedef struct _tag_RGB_struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} CMRGB;

#pragma pack(pop)

typedef enum {
    CM_YUV_FMT_400,
    CM_YUV_FMT_420,
    CM_YUV_FMT_422,
    CM_YUV_FMT_444
} CMYUVFormat;

class CMImage {
public:
    static CMRGB* convertYUVtoRGB(unsigned char* yuv, int width, int height, CMYUVFormat format);

};

#endif /* __CM_IMAGE_H__ */