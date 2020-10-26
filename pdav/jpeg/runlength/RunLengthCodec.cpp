#include "RunLengthCodec.h"

int sizeRanges[12][4] = {
        // Skip first 2 values to match index and size
        {},
        {},
        { -1, 0, 0, 1 },
        { -3, -2, 2, 3 },
        { -7, -4, 4, 7 },
        { -15, -8, 8, 15 },
        { -31, -16, 16, 31 },
        { -63, -32, 32, 63 },
        { -127, -64, 64, 127 },
        { -255, -128, 128, 255 },
        { -511, -256, 256, 511 },
        { -1023, -512, 512, 1023 },
};

unsigned int RunLengthCodec::getEncodingBits(int32_t &amplitude) const {
    for (int i = 2; i <= maxEncodingBits; i++) {
        if (sizeRanges[i][0] <= amplitude && amplitude <= sizeRanges[i][1] ||
                sizeRanges[i][2] <= amplitude && amplitude <= sizeRanges[i][3]) {
            return i;
        }
    }

    amplitude = std::max(amplitude, sizeRanges[maxEncodingBits][0]);
    amplitude = std::min(amplitude, sizeRanges[maxEncodingBits][3]);
    return maxEncodingBits;
}

unsigned int RunLengthCodec::getStorageBytes(uint8_t encodingBits) const {
    return encodingBits / 8 + !!(encodingBits % 8);
}

void RunLengthCodec::addEncodedData(std::vector<uint8_t> &targetData, const int32_t (&sourceData)[64]) {
    int stopAt = 64;

    for (int i = 63; i >= 0; i--) {
        if (sourceData[i] == 0) {
            stopAt = i;
        } else {
            break;
        }
    }

    int runLength = 0;
    for (int i = 0; i < stopAt; i++) {
        bool isDC = i == 0;
        int32_t amplitude = sourceData[i];
        if (amplitude == 0 && !isDC) {
            runLength++;
            continue;
        }

        if (!isDC) {
            targetData.push_back(runLength);
        }

        runLength = 0;

        unsigned int encodingBits = getEncodingBits(amplitude);
        targetData.push_back(encodingBits);

        unsigned int encodingBytes = getStorageBytes(encodingBits);
        uint32_t uAmplitude = amplitude;
        for (unsigned int bytesI = 0; bytesI < encodingBytes; bytesI++) {
            uint8_t value = (uAmplitude >> bytesI * 8) & 0xffu;
            targetData.push_back(value);
        }
    }

    if (stopAt != 64) {
        targetData.push_back(0);
        targetData.push_back(0);
    }
}

void RunLengthCodec::extractEncodedData(const std::vector<uint8_t> &sourceData, int32_t (&targetData)[64],
                                        size_t& sourceI, size_t sourceMaxI) {
    size_t baseSourceI = sourceI;
    size_t targetI = 0;

    while (sourceI < sourceMaxI && targetI < 64) {
        if (sourceData[sourceI] == 0 && sourceData[sourceI + 1] == 0) {
            sourceI += 2;
            break;
        }

        bool isDC = sourceI == baseSourceI;

        if (!isDC) {
            int runLength = sourceData[sourceI++];

            for (int i = 0; i < runLength; i++) {
                targetData[targetI++] = 0;;
            }
        }

        unsigned int encodingBits = sourceData[sourceI++];
        unsigned int encodingBytes = getStorageBytes(encodingBits);
        uint32_t uAmplitude = 0;

        unsigned int leftoverBytes = sizeof(uint32_t) - encodingBytes;
        for (unsigned int byteI = 0; byteI < encodingBytes; byteI++) {
            uAmplitude |= sourceData[sourceI++] << ((byteI + leftoverBytes) * 8);
        }

        int32_t amplitude = uAmplitude;
        amplitude = amplitude >> (leftoverBytes * 8);
        targetData[targetI++] = amplitude;
    }
}

void RunLengthCodec::encode(ZigZagImage &source, RunLengthImage &target) {
    target.resize(source.width(), source.height());

    for (uint32_t blockY = 0; blockY < source.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < source.dataWidth(); blockX++) {
            const auto &sourceBlock = source.dataAt(blockX, blockY);

            addEncodedData(target.data, sourceBlock.y);
            addEncodedData(target.data, sourceBlock.u);
            addEncodedData(target.data, sourceBlock.v);
        }
    }
}

void RunLengthCodec::decode(RunLengthImage &source, ZigZagImage &target) {
    target.resize(source.width(), source.height());

    size_t i = 0;
    size_t end = source.data.size();
    for (uint32_t blockY = 0; blockY < target.dataHeight(); blockY++) {
        for (uint32_t blockX  = 0; blockX < target.dataWidth(); blockX++) {
            auto &targetBlock = target.dataAt(blockX, blockY);

            extractEncodedData(source.data, targetBlock.y, i, end);
            extractEncodedData(source.data, targetBlock.u, i, end);
            extractEncodedData(source.data, targetBlock.v, i, end);
        }
    }
}
