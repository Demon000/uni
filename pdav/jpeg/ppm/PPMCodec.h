#ifndef JPEG_PPMCODEC_H
#define JPEG_PPMCODEC_H

#include "../RawImage.h"

class PPMCodec {
public:
    static void write(RawImage &image, std::ofstream &output);
    static void read(RawImage &image, std::ifstream& input);

private:
    static void readP3(RawImage &image, std::ifstream& input, uint32_t max);
    static void readP6(RawImage &image, std::ifstream& input, uint32_t max);
};

#endif //JPEG_PPMCODEC_H
