#ifndef JPEG_YUV444CODEC_H
#define JPEG_YUV444CODEC_H

#include "../yuv/RawYUVImage.h"
#include "YUV444Image.h"

class YUV444Codec {
public:
    void encode(RawYUVImage &source, YUV444Image &target);
    void decode(YUV444Image &source, RawYUVImage &target);
};


#endif //JPEG_YUV444CODEC_H
