#ifndef JPEG_YUVCODEC_H
#define JPEG_YUVCODEC_H


#include "../generic/RawRGBImage.h"
#include "RawYUVImage.h"

class YUVCodec {
public:
    void encode(RawRGBImage &source, RawYUVImage &target);
    void decode(RawYUVImage &source, RawRGBImage &target);
};


#endif //JPEG_YUVCODEC_H
