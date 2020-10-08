#ifndef JPEG_YUVCODEC_H
#define JPEG_YUVCODEC_H


#include "../RawImage.h"

class YUVCodec {
public:
    void decode(RawImage &source, RawImage &target);
    void encode(RawImage &source, RawImage &target);
};


#endif //JPEG_YUVCODEC_H
