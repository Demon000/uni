#ifndef JPEG_YUVIMAGE_H
#define JPEG_YUVIMAGE_H

#include <cstdint>

static constexpr uint32_t YUV_SOURCE_BLOCK_SIZE = 8;

template <typename D>
class YUVImage : public BlockImage<D> {
public:
    YUVImage() : BlockImage<D>(YUV_SOURCE_BLOCK_SIZE) {}
};

#endif //JPEG_YUVIMAGE_H
