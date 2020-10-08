#ifndef JPEG_YUV444CODEC_H
#define JPEG_YUV444CODEC_H


#include "../RawImage.h"
#include "YUV444Image.h"

class YUV444Codec {
public:
    void encode(RawImage &source, YUV444Image &target);
    void decode(YUV444Image &source, RawImage &target);
};


#endif //JPEG_YUV444CODEC_H
