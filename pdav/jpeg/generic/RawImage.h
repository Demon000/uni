#ifndef JPEG_RAWIMAGE_H
#define JPEG_RAWIMAGE_H

#include <string>
#include <memory>
#include <vector>

#include "Image.h"

struct Raw24BitData {
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;
};

class RawImage : public Image<Raw24BitData> {};


#endif //JPEG_RAWIMAGE_H
