#ifndef JPEG_DCTCODEC_H
#define JPEG_DCTCODEC_H


#include "../yuv444/YUV444Image.h"
#include "../generic/Int32Image.h"

class DCTCodec {
public:
    void encode(YUV444Image &source, Int32Image &target);
    void decode(Int32Image &source, YUV444Image &target);
};


#endif //JPEG_DCTCODEC_H
