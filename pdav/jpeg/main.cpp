#include <fstream>

#include "RawImage.h"
#include "ppm/PPMCodec.h"
#include "yuv444/YUV444Image.h"
#include "yuv/YUVCodec.h"
#include "yuv444/YUV444Codec.h"
#include "yuv420/YUV420Codec.h"
#include "dct/DCTCodec.h"

YUVCodec yuvCodec;
YUV444Codec yuv444Codec;
YUV420Codec yuv420Codec;
DCTCodec dctCodec;

void testReadImage(RawImage &image, const std::string& path) {
    std::ifstream input(path);
    PPMCodec::read(image, input);
}

void testWriteImage(RawImage& image, const std::string& path) {
    std::ofstream output(path);
    PPMCodec::write(image, output);
}

void evaluateConversion(RawImage& source, RawImage& target) {
    double x_error = 0;
    double y_error = 0;
    double z_error = 0;

    for (size_t i = 0; i < source.dataSize(); i++) {
        const auto& sourcePixel = source.dataAt(i);
        const auto& targetPixel = target.dataAt(i);
        double diff;

        diff = sourcePixel.x - targetPixel.x;
        x_error += diff;

        diff = sourcePixel.y - targetPixel.y;
        y_error += diff;

        diff = sourcePixel.z - targetPixel.z;
        z_error += diff;
    }

    x_error /= source.dataSize();
    y_error /= source.dataSize();
    z_error /= source.dataSize();

    std::cout << "x_error: " << x_error << ", y_error: " << y_error << ", z_error: " << z_error << std::endl;
}

void testConvertRawYUV(RawImage& image, RawImage& target) {
    RawImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertYUV444(RawImage& image, RawImage& target) {
    YUV444Image yuv444Image;
    RawImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertYUV420(RawImage& image, RawImage& target) {
    YUV444Image yuv444Image;
    YUV420Image yuv420Image;
    RawImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv420Codec.encode(yuv444Image, yuv420Image);
    yuv420Codec.decode(yuv420Image, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertDCT(RawImage& image, RawImage& target) {
    YUV444Image yuv444Image;
    Int32Image int32Image;
    YUV420Image yuv420Image;
    RawImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv420Codec.encode(yuv444Image, yuv420Image);
    yuv420Codec.decode(yuv420Image, yuv444Image);
    dctCodec.encode(yuv444Image, int32Image);
    dctCodec.decode(int32Image, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

int main() {
    RawImage image;
    RawImage tempImage;

    testReadImage(image, "nt-P3.ppm");
    testWriteImage(image, "nt-P3-out.ppm");

    testConvertRawYUV(image, tempImage);
    evaluateConversion(image, tempImage);
    testWriteImage(tempImage, "nt-P3-out-rgb-yuv-rgb.ppm");

    testConvertYUV444(image, tempImage);
    evaluateConversion(image, tempImage);
    testWriteImage(tempImage, "nt-P3-out-rgb-yuv-yuv444-yuv-rgb.ppm");

    testConvertYUV420(image, tempImage);
    evaluateConversion(image, tempImage);
    testWriteImage(tempImage, "nt-P3-out-rgb-yuv-yuv444-yuv420-yuv444-yuv-rgb.ppm");

    testConvertDCT(image, tempImage);
    evaluateConversion(image, tempImage);
    testWriteImage(tempImage, "nt-P3-out-rgb-yuv-yuv444-yuv420-yuv444-dct-yuv444-yuv-rgb.ppm");

    return 0;
}
