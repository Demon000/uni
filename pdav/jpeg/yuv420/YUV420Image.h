#ifndef JPEG_YUV420IMAGE_H
#define JPEG_YUV420IMAGE_H

#include <cstdint>
#include "../generic/BlockImage.h"
#include "../yuv/YUVImage.h"

static constexpr int YUV420_U_V_BLOCK_SIZE = 4;
static constexpr int YUV420_U_V_GROUP_SIZE = YUV_SOURCE_BLOCK_SIZE / YUV420_U_V_BLOCK_SIZE;

struct YUV420Data {
    uint8_t y[YUV_SOURCE_BLOCK_SIZE][YUV_SOURCE_BLOCK_SIZE] = {0};
    uint8_t u[YUV420_U_V_BLOCK_SIZE][YUV420_U_V_BLOCK_SIZE] = {0};
    uint8_t v[YUV420_U_V_BLOCK_SIZE][YUV420_U_V_BLOCK_SIZE] = {0};
};

class YUV420Image : public YUVImage<YUV420Data> {};

#endif //JPEG_YUV420IMAGE_H
