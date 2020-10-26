#ifndef JPEG_ZIGZAGIMAGE_H
#define JPEG_ZIGZAGIMAGE_H

#include "../generic/BlockImage.h"

struct ZigZagData {
    int32_t y[64] = {0};
    int32_t u[64] = {0};
    int32_t v[64] = {0};
};

class ZigZagImage : public BlockImage<ZigZagData> {
public:
    ZigZagImage() : BlockImage(8) {}
};

#endif //JPEG_ZIGZAGIMAGE_H
