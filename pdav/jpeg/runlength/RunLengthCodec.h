#ifndef JPEG_RUNLENGTHCODEC_H
#define JPEG_RUNLENGTHCODEC_H

#include "../zigzag/ZigZagImage.h"
#include "RunLengthImage.h"

class RunLengthCodec {
public:
    RunLengthCodec(unsigned int maxEncodingBits=8) : maxEncodingBits(maxEncodingBits) {}

    void encode(ZigZagImage &source, RunLengthImage &target);
    void decode(RunLengthImage &source, ZigZagImage &target);

private:
    unsigned int getEncodingBits(int32_t &amplitude) const;
    unsigned int getStorageBytes(uint8_t encodingBits) const;
    void addEncodedData(std::vector<uint8_t> &targetData, const int32_t (&sourceData)[64]);
    void extractEncodedData(const std::vector<uint8_t> &sourceData, int32_t (&targetData)[64], size_t &sourceI, size_t sourceMaxI);

    unsigned int maxEncodingBits;
};

#endif //JPEG_RUNLENGTHCODEC_H
