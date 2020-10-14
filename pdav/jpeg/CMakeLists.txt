cmake_minimum_required(VERSION 3.17)
project(jpeg CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(jpeg main.cpp generic/Image.h generic/RawImage.h generic/BlockImage.h ppm/PPMCodec.cpp ppm/PPMCodec.h yuv444/YUV444Image.h yuv420/YUV420Image.h yuv/YUVImage.h generic/Int32Image.h yuv/YUVCodec.cpp yuv/YUVCodec.h utils/utils.h utils/utils.cpp yuv444/YUV444Codec.cpp yuv444/YUV444Codec.h yuv420/YUV420Codec.cpp yuv420/YUV420Codec.h dct/DCTCodec.cpp dct/DCTCodec.h qnt/QNTCodec.cpp qnt/QNTCodec.h generic/RawRGBImage.h yuv/RawYUVImage.h dct/DCTImage.h qnt/QNTImage.h)
configure_file(nt-P3.ppm nt-P3.ppm COPYONLY)
configure_file(nt-P6.ppm nt-P6.ppm COPYONLY)
