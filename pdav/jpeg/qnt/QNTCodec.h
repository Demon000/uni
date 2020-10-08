#ifndef JPEG_QNTCODEC_H
#define JPEG_QNTCODEC_H


#include "../generic/Int32Image.h"

class QNTCodec {
public:
    void encode(Int32Image &source, Int32Image &target);
    void decode(Int32Image &source, Int32Image &target);
};


#endif //JPEG_QNTCODEC_H
