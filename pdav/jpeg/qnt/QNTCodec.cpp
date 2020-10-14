#include "QNTCodec.h"

void QNTCodec::encode(DCTImage &source, QNTImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < 8; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < 8; relativeX++) {
                    targetBlock.y[relativeY][relativeX] = sourceBlock.y[relativeY][relativeX]
                            / quantizationTable[relativeY][relativeX];
                    targetBlock.u[relativeY][relativeX] = sourceBlock.u[relativeY][relativeX]
                            / quantizationTable[relativeY][relativeX];
                    targetBlock.v[relativeY][relativeX] = sourceBlock.v[relativeY][relativeX]
                            / quantizationTable[relativeY][relativeX];
                }
            }
        }
    }
}

void QNTCodec::decode(QNTImage &source, DCTImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            for (uint32_t relativeY = 0; relativeY < 8; relativeY++) {
                for (uint32_t relativeX = 0; relativeX < 8; relativeX++) {
                    targetBlock.y[relativeY][relativeX] = sourceBlock.y[relativeY][relativeX]
                                                          * quantizationTable[relativeY][relativeX];
                    targetBlock.u[relativeY][relativeX] = sourceBlock.u[relativeY][relativeX]
                                                          * quantizationTable[relativeY][relativeX];
                    targetBlock.v[relativeY][relativeX] = sourceBlock.v[relativeY][relativeX]
                                                          * quantizationTable[relativeY][relativeX];
                }
            }
        }
    }
}
