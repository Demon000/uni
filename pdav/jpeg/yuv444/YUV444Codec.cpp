#include <cassert>
#include "YUV444Codec.h"
#include "../RawImage.h"
#include "YUV444Image.h"

void YUV444Codec::encode(RawImage &source, YUV444Image &target) {
    assert(source.type == RawImageType::RAW_YUV);

    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < target.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < target.dataWidth(); blockX++) {
            auto& block = target.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < YUV_SOURCE_BLOCK_SIZE; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < YUV_SOURCE_BLOCK_SIZE; relativeX++) {
                    uint32_t pixelX = blockX * YUV_SOURCE_BLOCK_SIZE + relativeX;
                    uint32_t pixelY = blockY * YUV_SOURCE_BLOCK_SIZE + relativeY;
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

void YUV444Codec::decode(YUV444Image &source, RawImage &target) {
    target.type = RawImageType::RAW_YUV;
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& block = source.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < YUV_SOURCE_BLOCK_SIZE; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < YUV_SOURCE_BLOCK_SIZE; relativeX++) {
                    uint32_t pixelX = blockX * YUV_SOURCE_BLOCK_SIZE + relativeX;
                    uint32_t pixelY = blockY * YUV_SOURCE_BLOCK_SIZE + relativeY;
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
