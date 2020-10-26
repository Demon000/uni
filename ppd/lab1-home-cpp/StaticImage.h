#ifndef LAB1_HOME_CPP_STATICIMAGE_H
#define LAB1_HOME_CPP_STATICIMAGE_H


#include "Image.h"

#define STATIC_IMAGE_SIZE 1000

class StaticImage : public Image {
public:
    void setPixel(int i, int value) override {
        pixels[i] = value;
    }

    int getPixel(int i) override {
        return pixels[i];
    }

private:
    uint8_t pixels[STATIC_IMAGE_SIZE * STATIC_IMAGE_SIZE] = {};
};


#endif //LAB1_HOME_CPP_STATICIMAGE_H
