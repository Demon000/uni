#include "../utils/utils.h"
#include "YUVCodec.h"

void pixelRGBtoYUV(const struct Raw24BitData& source, struct Raw24BitData& target) {
    double x =   0 + 0.299    * source.x + 0.587    * source.y + 0.114    * source.z;
    double y = 128 - 0.168736 * source.x - 0.331264 * source.y + 0.5      * source.z;
    double z = 128 + 0.5      * source.x - 0.418688 * source.y - 0.081312 * source.z;

    target.x = clampByte(x);
    target.y = clampByte(y);
    target.z = clampByte(z);
}

void pixelYUVtoRGB(const struct Raw24BitData& source, struct Raw24BitData& target) {
    double x = source.x                               + 1.402    * (source.z - 128);
    double y = source.x - 0.344136 * (source.y - 128) - 0.714136 * (source.z - 128);
    double z = source.x + 1.772    * (source.y - 128);

    target.x = clampByte(x);
    target.y = clampByte(y);
    target.z = clampByte(z);
}

template<typename F>
void rawPixelConversion(RawImage &source, RawImage &target, F f) {
    target.resize(source.width(), source.height());

    for (uint32_t i = 0; i < source.dataSize(); i++) {
        const auto& sourcePixel = source.dataAt(i);
        auto& targetPixel = target.dataAt(i);

        f(sourcePixel, targetPixel);
    }
}

void YUVCodec::encode(RawRGBImage &source, RawYUVImage &target) {
    rawPixelConversion(source, target, pixelRGBtoYUV);
}

void YUVCodec::decode(RawYUVImage &source, RawRGBImage &target) {
    rawPixelConversion(source, target, pixelYUVtoRGB);
}
