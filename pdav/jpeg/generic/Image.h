#ifndef JPEG_IMAGE_H
#define JPEG_IMAGE_H

#include <cstdint>
#include <iostream>

class Image {
public:
    uint32_t width() const {
        return width_;
    }

    uint32_t height() const {
        return height_;
    }

    virtual void resize(uint32_t width, uint32_t  height) {
        width_ = width;
        height_ = height;
    }

    virtual void dump() const {
        std::cout << "Image -> width: " << width_ << ", height: " << height_ << std::endl;
    }

protected:
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

#endif //JPEG_IMAGE_H
