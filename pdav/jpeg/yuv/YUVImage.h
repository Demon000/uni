#ifndef JPEG_YUVIMAGE_H
#define JPEG_YUVIMAGE_H

#include <cstdint>

template <typename D>
class YUVImage : public BlockImage<D> {
public:
    YUVImage() : BlockImage<D>(8) {}
};

#endif //JPEG_YUVIMAGE_H
