#ifndef JPEG_YUV420CODEC_H
#define JPEG_YUV420CODEC_H

#include "../yuv444/YUV444Image.h"
#include "YUV420Image.h"

class YUV420Codec {
public:
    void encode(YUV444Image &source, YUV420Image &target);
    void decode(YUV420Image &source, YUV444Image &target);
};


#endif //JPEG_YUV420CODEC_H
