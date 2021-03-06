#include <cmath>
#include "DCTCodec.h"
#include "../utils/utils.h"

double alpha(double value) {
    if (value == 0) {
        return 1 / sqrt(2);
    } else {
        return 1;
    }
}

void runForwardDCT(const uint8_t (&source)[8][8],
                   int32_t (&target)[8][8]) {
    for (uint32_t targetY = 0; targetY < 8; targetY++) {
        for (uint32_t targetX = 0; targetX < 8; targetX++) {
            double targetValue = (1.0 / 4.0) * alpha(targetY) * alpha(targetX);
            double sourceValuesSum = 0;
            for (uint32_t sourceY = 0; sourceY < 8; sourceY++) {
                for (uint32_t sourceX = 0; sourceX < 8; sourceX++) {
                    double sourceValue = source[sourceY][sourceX] - 128;
                    sourceValue *= cos(((2 * sourceX + 1) * targetX * M_PI) / 16);
                    sourceValue *= cos(((2 * sourceY + 1) * targetY * M_PI) / 16);
                    sourceValuesSum += sourceValue;
                }
            }
            targetValue *= sourceValuesSum;
            target[targetY][targetX] = targetValue;
        }
    }
}

void runBackwardDCT(const int32_t (&source)[8][8],
                    uint8_t (&target)[8][8]) {
    for (uint32_t targetY = 0; targetY < 8; targetY++) {
        for (uint32_t targetX = 0; targetX < 8; targetX++) {
            double targetValue = (1.0 / 4.0);
            double sourceValuesSum = 0;
            for (uint32_t sourceY = 0; sourceY < 8; sourceY++) {
                for (uint32_t sourceX = 0; sourceX < 8; sourceX++) {
                    double sourceValue = alpha(sourceY) * alpha(sourceX) * source[sourceY][sourceX];
                    sourceValue *= cos(((2 * targetX + 1) * sourceX * M_PI) / 16);
                    sourceValue *= cos(((2 * targetY + 1) * sourceY * M_PI) / 16);
                    sourceValuesSum += sourceValue;
                }
            }
            targetValue *= sourceValuesSum;
            targetValue += 128;
            target[targetY][targetX] = clampByte(targetValue);
        }
    }
}

void DCTCodec::encode(YUV444Image &source, DCTImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            runForwardDCT(sourceBlock.y, targetBlock.y);
            runForwardDCT(sourceBlock.u, targetBlock.u);
            runForwardDCT(sourceBlock.v, targetBlock.v);
        }
    }
}

void DCTCodec::decode(DCTImage &source, YUV444Image &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto& sourceBlock = source.dataAt(blockX, blockY);
            auto& targetBlock = target.dataAt(blockX, blockY);

            runBackwardDCT(sourceBlock.y, targetBlock.y);
            runBackwardDCT(sourceBlock.u, targetBlock.u);
            runBackwardDCT(sourceBlock.v, targetBlock.v);
        }
    }
}
