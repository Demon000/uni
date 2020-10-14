#ifndef JPEG_DCTCODEC_H
#define JPEG_DCTCODEC_H


#include "../yuv444/YUV444Image.h"
#include "DCTImage.h"

class DCTCodec {
public:
    void encode(YUV444Image &source, DCTImage &target);
    void decode(DCTImage &source, YUV444Image &target);
};


#endif //JPEG_DCTCODEC_H
