#ifndef LAB1_HOME_CPP_DYNAMICIMAGE_H
#define LAB1_HOME_CPP_DYNAMICIMAGE_H


#include <vector>
#include "Image.h"

class DynamicImage : public Image {
public:
    void setPixel(int i, int value) override {
        pixels[i] = value;
    }

    int getPixel(int i) override {
        return pixels[i];
    }

    void resize(int w, int h) {
        Image::resize(w, h);
        pixels.resize(w * h);
    }

private:
    std::vector<uint8_t> pixels;
};


#endif //LAB1_HOME_CPP_DYNAMICIMAGE_H
