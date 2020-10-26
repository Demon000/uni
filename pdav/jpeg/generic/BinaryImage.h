#ifndef JPEG_BINARYIMAGE_H
#define JPEG_BINARYIMAGE_H

#include <vector>
#include "Image.h"

class BinaryImage : public Image {
public:
    std::vector<uint8_t > data;
};

#endif //JPEG_BINARYIMAGE_H
