#ifndef JPEG_INT32IMAGE_H
#define JPEG_INT32IMAGE_H

#include <cstdint>
#include "../generic/BlockImage.h"

struct Int32ImageData {
    int32_t y[8][8] = {0};
    int32_t u[8][8] = {0};
    int32_t v[8][8] = {0};
};

class Int32Image : public BlockImage<struct Int32ImageData> {
public:
    Int32Image() : BlockImage(8) {}
};

#endif //JPEG_INT32IMAGE_H
