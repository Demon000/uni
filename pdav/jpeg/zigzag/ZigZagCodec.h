#ifndef JPEG_ZIGZAGCODEC_H
#define JPEG_ZIGZAGCODEC_H

#include "../qnt/QNTImage.h"
#include "ZigZagImage.h"

class ZigZagCodec {
public:
    void encode(QNTImage &source, ZigZagImage &target);
    void decode(ZigZagImage &source, QNTImage &target);
};

#endif //JPEG_ZIGZAGCODEC_H
