#ifndef JPEG_RAWIMAGE_H
#define JPEG_RAWIMAGE_H

#include <string>
#include <memory>
#include <vector>

#include "generic/Image.h"

enum RawImageType {
    RAW_UNKNOWN,
    RAW_RGB,
    RAW_YUV,
};

struct Raw24BitData {
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;
};

class RawImage : public Image<Raw24BitData> {
public:
    RawImageType type = RawImageType::RAW_UNKNOWN;
};


#endif //JPEG_RAWIMAGE_H
