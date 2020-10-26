#include "ZigZagCodec.h"

uint8_t linearYXMap[64][2] {
        { 0, 0 },
        { 0, 1 },
        { 1, 0 },
        { 2, 0 },
        { 1, 1 },
        { 0, 2 },
        { 0, 3 },
        { 1, 2 },
        { 2, 1 },
        { 3, 0 },
        { 4, 0 },
        { 3, 1 },
        { 2, 2 },
        { 1, 3 },
        { 0, 4 },
        { 0, 5 },
        { 1, 4 },
        { 2, 3 },
        { 3, 2 },
        { 4, 1 },
        { 5, 0 },
        { 6, 0 },
        { 5, 1 },
        { 4, 2 },
        { 3, 3 },
        { 2, 4 },
        { 1, 5 },
        { 0, 6 },
        { 0, 7 },
        { 1, 6 },
        { 2, 5 },
        { 3, 4 },
        { 4, 3 },
        { 5, 2 },
        { 6, 1 },
        { 7, 0 },
        { 7, 1 },
        { 6, 2 },
        { 5, 3 },
        { 4, 4 },
        { 3, 5 },
        { 2, 6 },
        { 1, 7 },
        { 2, 7 },
        { 3, 6 },
        { 4, 5 },
        { 5, 4 },
        { 6, 3 },
        { 7, 2 },
        { 7, 3 },
        { 6, 4 },
        { 5, 5 },
        { 4, 6 },
        { 3, 7 },
        { 4, 7 },
        { 5, 6 },
        { 6, 5 },
        { 7, 4 },
        { 7, 5 },
        { 6, 6 },
        { 5, 7 },
        { 6, 7 },
        { 7, 6 },
        { 7, 7 },
};

void ZigZagCodec::encode(QNTImage &source, ZigZagImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            for (int i = 0; i < 64; i++) {
                int relativeY = linearYXMap[i][0];
                int relativeX = linearYXMap[i][1];

                targetBlock.y[i] = sourceBlock.y[relativeY][relativeX];
                targetBlock.u[i] = sourceBlock.u[relativeY][relativeX];
                targetBlock.v[i] = sourceBlock.v[relativeY][relativeX];
            }
        }
    }
}

void ZigZagCodec::decode(ZigZagImage &source, QNTImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            for (int i = 0; i < 64; i++) {
                int relativeY = linearYXMap[i][0];
                int relativeX = linearYXMap[i][1];

                targetBlock.y[relativeY][relativeX] = sourceBlock.y[i];
                targetBlock.u[relativeY][relativeX] = sourceBlock.u[i];
                targetBlock.v[relativeY][relativeX] = sourceBlock.v[i];
            }
        }
    }
}
