#include "YUV444Codec.h"

void YUV444Codec::encode(RawYUVImage &source, YUV444Image &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < target.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < target.dataWidth(); blockX++) {
            auto& block = target.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < 8; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < 8; relativeX++) {
                    uint32_t pixelX = blockX * 8 + relativeX;
                    uint32_t pixelY = blockY * 8 + relativeY;
                    if (pixelX >= target.width() || pixelY >= target.height()) {
                        continue;
                    }

                    const auto& pixel = source.dataAt(pixelX, pixelY);
                    block.y[relativeY][relativeX] = pixel.x;
                    block.u[relativeY][relativeX] = pixel.y;
                    block.v[relativeY][relativeX] = pixel.z;
                }
            }
        }
    }
}

void YUV444Codec::decode(YUV444Image &source, RawYUVImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& block = source.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < 8; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < 8; relativeX++) {
                    uint32_t pixelX = blockX * 8 + relativeX;
                    uint32_t pixelY = blockY * 8 + relativeY;
                    if (pixelX >= target.width() || pixelY >= target.height()) {
                        continue;
                    }

                    auto& pixel = target.dataAt(pixelX, pixelY);
                    pixel.x = block.y[relativeY][relativeX];
                    pixel.y = block.u[relativeY][relativeX];
                    pixel.z = block.v[relativeY][relativeX];
                }
            }
        }
    }
}
