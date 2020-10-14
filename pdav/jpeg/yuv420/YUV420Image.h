#ifndef JPEG_YUV420IMAGE_H
#define JPEG_YUV420IMAGE_H

#include <cstdint>
#include "../generic/BlockImage.h"
#include "../yuv/YUVImage.h"

struct YUV420Data {
    uint8_t y[8][8] = {0};
    uint8_t u[4][4] = {0};
    uint8_t v[4][4] = {0};
};

class YUV420Image : public YUVImage<YUV420Data> {};

#endif //JPEG_YUV420IMAGE_H
