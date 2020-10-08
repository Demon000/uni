#ifndef JPEG_BLOCKIMAGE_H
#define JPEG_BLOCKIMAGE_H

#include "Image.h"

template <typename D>
class BlockImage : public Image<D> {
public:
    BlockImage(uint32_t sourceBlockSize) : sourceBlockSize(sourceBlockSize) {}

    void resize(uint32_t width, uint32_t height) override {
        uint32_t dataWidth = width / sourceBlockSize + !!(width % sourceBlockSize);
        uint32_t dataHeight = height / sourceBlockSize + !!(height % sourceBlockSize);
        Image<D>::resize(width, height, dataWidth, dataHeight);
    }

    void dump() const override {
        Image<D>::dump();
    }

protected:
    uint32_t sourceBlockSize;
};

#endif //JPEG_BLOCKIMAGE_H
