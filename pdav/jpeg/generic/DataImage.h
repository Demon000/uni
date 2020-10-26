#ifndef JPEG_DATAIMAGE_H
#define JPEG_DATAIMAGE_H

#include <cstdint>
#include <iostream>
#include <iostream>
#include <memory>
#include <vector>
#include "Image.h"

template <typename D>
class DataImage : public Image {
public:
    virtual uint32_t dataWidth() const {
        return dataWidth_;
    }

    virtual uint32_t dataHeight() const {
        return dataHeight_;
    }

    uint32_t dataSize() const {
        return data.size();
    }

    virtual void resize(uint32_t width, uint32_t  height, uint32_t dataWidth, uint32_t dataHeight) {
        Image::resize(width, height);
        dataWidth_ = dataWidth;
        dataHeight_ = dataHeight;
        data.clear();
        data.resize(dataWidth * dataHeight);
    }

    virtual void resize(uint32_t width, uint32_t height) {
        resize(width, height, width, height);
    }

    virtual D& dataAt(uint32_t i) {
        return data.at(i);
    }

    virtual D& dataAt(uint32_t x, uint32_t y) {
        return dataAt(y * dataWidth_ + x);
    }

    virtual void dump() const override {
        Image::dump();
        std::cout << "dataWidth: " << dataWidth_ << ", dataHeight: " << dataHeight_
                << ", dataSize: " << dataSize() << std::endl;
    }

protected:
    std::vector<D> data;
    uint32_t dataWidth_ = 0;
    uint32_t dataHeight_ = 0;
};


#endif //JPEG_DATAIMAGE_H
