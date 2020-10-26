#ifndef JPEG_PPMCODEC_H
#define JPEG_PPMCODEC_H

#include "../generic/RawRGBImage.h"

class PPMCodec {
public:
    static void write(RawRGBImage &image, std::ofstream &output);
    static void read(RawRGBImage &image, std::ifstream &input);

private:
    static void readP3(RawRGBImage &image, std::ifstream &input, uint32_t max);
    static void readP6(RawRGBImage &image, std::ifstream &input, uint32_t max);
};

#endif //JPEG_PPMCODEC_H
