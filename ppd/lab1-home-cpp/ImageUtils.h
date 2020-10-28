#ifndef LAB1_HOME_CPP_IMAGEUTILS_H
#define LAB1_HOME_CPP_IMAGEUTILS_H

#include "Image.h"

class ImageUtils {
public:
    static void copyPixels(Image &source, Image &target) {
        if (source.getSize() != target.getSize()) {
            throw std::runtime_error("Cannot copy pixels when sizes don't match");
        }

        if (source.isSkip() && target.isSkip()) {
            copyPixels(source, 0, target, 0, source.getRealSize());
        } else if (source.isSkip() && !target.isSkip()) {
            copyPixels(source, 0, target, source.getStart(), source.getRealSize());
        } else if (!source.isSkip() && target.isSkip()) {
            copyPixels(source, target.getStart(), target, 0, target.getRealSize());
        } else {
            copyPixels(source, 0, target, 0, source.getRealSize());
        }
    }

    static void copyPixels(Image &source, int sourceStart, Image &target, int targetStart, int length) {
        std::copy(source.getPixels().begin() + sourceStart,
                  source.getPixels().begin() + sourceStart + length,
                  target.getPixels().begin() + targetStart);
    }
};

#endif //LAB1_HOME_CPP_IMAGEUTILS_H
