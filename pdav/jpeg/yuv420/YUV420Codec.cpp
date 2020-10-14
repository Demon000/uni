#include "YUV420Codec.h"
#include "YUV420Image.h"

void YUV420Codec::encode(YUV444Image &source, YUV420Image &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < 8; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < 8; relativeX++) {
                    targetBlock.y[relativeY][relativeX] = sourceBlock.y[relativeY][relativeX];
                }
            }

            for (uint32_t sampledY = 0; sampledY < 4; sampledY++) {
                for (uint32_t sampledX = 0; sampledX < 4; sampledX++) {
                    double averageU = 0, averageV = 0;
                    int count = 0;
                    for (uint32_t relativeY = 0; relativeY < 2; relativeY++) {
                        for (uint32_t relativeX = 0; relativeX < 2; relativeX++) {
                            uint32_t unsampledX = sampledX * 2 + relativeX;
                            uint32_t unsampledY = sampledY * 2 + relativeY;
                            uint32_t pixelX = blockX * 8 + unsampledX;
                            uint32_t pixelY = blockY * 8 + unsampledY;
                            if (pixelX >= target.width() || pixelY >= target.height()) {
                                continue;
                            }

                            count += 1;
                            averageU += sourceBlock.u[unsampledY][unsampledX];
                            averageV += sourceBlock.v[unsampledY][unsampledX];
                        }
                    }
                    targetBlock.u[sampledY][sampledX] = averageU / count;
                    targetBlock.v[sampledY][sampledX] = averageV / count;
                }
            }
        }
    }
}

void YUV420Codec::decode(YUV420Image &source, YUV444Image &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < 8; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < 8; relativeX++) {
                    targetBlock.y[relativeY][relativeX] = sourceBlock.y[relativeY][relativeX];
                }
            }

            for (uint32_t sampledY = 0; sampledY < 4; sampledY++) {
                for (uint32_t sampledX = 0; sampledX < 4; sampledX++) {
                    uint8_t averageU = sourceBlock.u[sampledY][sampledX];
                    uint8_t averageV = sourceBlock.v[sampledY][sampledX];
                    for (uint32_t relativeY = 0; relativeY < 2; relativeY++) {
                        for (uint32_t relativeX = 0; relativeX < 2; relativeX++) {
                            uint32_t unsampledX = sampledX * 2 + relativeX;
                            uint32_t unsampledY = sampledY * 2 + relativeY;
                            uint32_t pixelX = blockX * 8 + unsampledX;
                            uint32_t pixelY = blockY * 8 + unsampledY;
                            if (pixelX >= target.width() || pixelY >= target.height()) {
                                continue;
                            }

                            targetBlock.u[unsampledY][unsampledX] = averageU;
                            targetBlock.v[unsampledY][unsampledX] = averageV;
                        }
                    }
                }
            }
        }
    }
}
