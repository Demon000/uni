#ifndef JPEG_INT32IMAGE_H
#define JPEG_INT32IMAGE_H

#include <cstdint>
#include "../generic/BlockImage.h"

static constexpr uint32_t DCT_BLOCK_SIZE = 8;

enum Int32ImageType {
    INT32_UNKNOWN,
    INT32_DCT,
    INT32_QNT,
};

struct Int32ImageData {
    int32_t y[DCT_BLOCK_SIZE][DCT_BLOCK_SIZE] = {0};
    int32_t u[DCT_BLOCK_SIZE][DCT_BLOCK_SIZE] = {0};
    int32_t v[DCT_BLOCK_SIZE][DCT_BLOCK_SIZE] = {0};
};

class Int32Image : public BlockImage<struct Int32ImageData> {
public:
    Int32Image() : BlockImage(DCT_BLOCK_SIZE) {}

    Int32ImageType type = Int32ImageType::INT32_UNKNOWN;
};

#endif //JPEG_INT32IMAGE_H
