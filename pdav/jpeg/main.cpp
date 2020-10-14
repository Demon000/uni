#include <fstream>

#include "generic/RawImage.h"
#include "ppm/PPMCodec.h"
#include "yuv444/YUV444Image.h"
#include "yuv/YUVCodec.h"
#include "yuv444/YUV444Codec.h"
#include "yuv420/YUV420Codec.h"
#include "dct/DCTCodec.h"
#include "qnt/QNTCodec.h"

void testReadImage(RawRGBImage &image, const std::string& path) {
    std::ifstream input(path);
    PPMCodec::read(image, input);
}

void testWriteImage(RawRGBImage& image, const std::string& path) {
    std::ofstream output(path);
    PPMCodec::write(image, output);
}

void evaluateConversion(RawRGBImage& source, RawRGBImage& target) {
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

void testConvertRawYUV(RawRGBImage& image, RawRGBImage& target, YUVCodec& yuvCodec) {
    RawYUVImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertYUV444(RawRGBImage& image, RawRGBImage& target,
                       YUVCodec& yuvCodec, YUV444Codec& yuv444Codec) {
    YUV444Image yuv444Image;
    RawYUVImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertYUV420(RawRGBImage& image, RawRGBImage& target,
                       YUVCodec& yuvCodec, YUV444Codec& yuv444Codec,
                       YUV420Codec& yuv420Codec) {
    YUV444Image yuv444Image;
    YUV420Image yuv420Image;
    RawYUVImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv420Codec.encode(yuv444Image, yuv420Image);
    yuv420Codec.decode(yuv420Image, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertDCT(RawRGBImage& image, RawRGBImage& target,
                    YUVCodec& yuvCodec, YUV444Codec& yuv444Codec,
                    YUV420Codec& yuv420Codec, DCTCodec& dctCodec) {
    YUV444Image yuv444Image;
    DCTImage dctImage;
    YUV420Image yuv420Image;
    RawYUVImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv420Codec.encode(yuv444Image, yuv420Image);
    yuv420Codec.decode(yuv420Image, yuv444Image);
    dctCodec.encode(yuv444Image, dctImage);
    dctCodec.decode(dctImage, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

void testConvertQNT(RawRGBImage& image, RawRGBImage& target,
                    YUVCodec& yuvCodec, YUV444Codec& yuv444Codec,
                    YUV420Codec& yuv420Codec, DCTCodec& dctCodec,
                    QNTCodec& qntCodec) {
    YUV444Image yuv444Image;
    DCTImage dctImage;
    QNTImage qntImage;
    YUV420Image yuv420Image;
    RawYUVImage yuvImage;

    yuvCodec.encode(image, yuvImage);
    yuv444Codec.encode(yuvImage, yuv444Image);
    yuv420Codec.encode(yuv444Image, yuv420Image);
    yuv420Codec.decode(yuv420Image, yuv444Image);
    dctCodec.encode(yuv444Image, dctImage);
    qntCodec.encode(dctImage, qntImage);
    qntCodec.decode(qntImage, dctImage);
    dctCodec.decode(dctImage, yuv444Image);
    yuv444Codec.decode(yuv444Image, yuvImage);
    yuvCodec.decode(yuvImage, target);
}

int main() {
    YUVCodec yuvCodec;
    YUV444Codec yuv444Codec;
    YUV420Codec yuv420Codec;
    DCTCodec dctCodec;
    QNTCodec qntCodec;
    RawRGBImage image;
    RawRGBImage tempImage;

    testReadImage(image, "nt-P3.ppm");
    testWriteImage(image, "nt-P3-out.ppm");

    testConvertQNT(image, tempImage, yuvCodec, yuv444Codec, yuv420Codec, dctCodec, qntCodec);
    evaluateConversion(image, tempImage);
    testWriteImage(tempImage, "nt-P3-out-rgb-yuv-yuv444-yuv420-yuv444-dct-qnt-dct-yuv444-yuv-rgb.ppm");

    return 0;
}