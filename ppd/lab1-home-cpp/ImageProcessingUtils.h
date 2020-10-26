#ifndef LAB1_HOME_CPP_IMAGEPROCESSINGUTILS_H
#define LAB1_HOME_CPP_IMAGEPROCESSINGUTILS_H


#include "Image.h"

class ImageProcessingUtils {
public:
    static void averagePixels(Image *source, Image *target, int x, int y, int size) {
        int average = 0;
        int count = 0;

        for (int i = y - size + 1; i <= y; i++) {
            if (i < 0 || i >= source->height) {
                continue;
            }

            for (int j = x - size + 1; j <= x; j++) {
                if (j < 0 || j >= source->width) {
                    continue;
                }

                average += source->getPixel(j, i);
                count++;
            }
        }

        if (count == 0) {
            average = 0;
        } else {
            average /= count;
        }

        target->setPixel(x, y, average);
    }
};


#endif //LAB1_HOME_CPP_IMAGEPROCESSINGUTILS_H
