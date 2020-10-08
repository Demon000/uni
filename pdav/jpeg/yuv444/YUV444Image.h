#ifndef JPEG_YUV444IMAGE_H
#define JPEG_YUV444IMAGE_H

#include <cstdint>
#include "../generic/BlockImage.h"
#include "../yuv/YUVImage.h"

struct YUV444Data {
    uint8_t y[YUV_SOURCE_BLOCK_SIZE][YUV_SOURCE_BLOCK_SIZE] = {0};
    uint8_t u[YUV_SOURCE_BLOCK_SIZE][YUV_SOURCE_BLOCK_SIZE] = {0};
    uint8_t v[YUV_SOURCE_BLOCK_SIZE][YUV_SOURCE_BLOCK_SIZE] = {0};
};

class YUV444Image : public YUVImage<YUV444Data> {};

#endif //JPEG_YUV444IMAGE_H
