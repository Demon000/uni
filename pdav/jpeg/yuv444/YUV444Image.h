#ifndef JPEG_YUV444IMAGE_H
#define JPEG_YUV444IMAGE_H

#include <cstdint>
#include "../generic/BlockImage.h"
#include "../yuv/YUVImage.h"

struct YUV444Data {
    uint8_t y[8][8] = {0};
    uint8_t u[8][8] = {0};
    uint8_t v[8][8] = {0};
};

class YUV444Image : public YUVImage<YUV444Data> {};

#endif //JPEG_YUV444IMAGE_H
