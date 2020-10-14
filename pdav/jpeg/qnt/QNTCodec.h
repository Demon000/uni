#ifndef JPEG_QNTCODEC_H
#define JPEG_QNTCODEC_H

#include <cstring>
#include "../generic/Int32Image.h"
#include "../dct/DCTImage.h"
#include "QNTImage.h"

typedef int32_t qtable_t[8][8];

static qtable_t defaultQuantizationTable = {
        {  6,  4,  4,  6, 10, 16, 20, 24, },
        {  5,  5,  6,  8, 10, 23, 24, 22, },
        {  6,  5,  6, 10, 16, 23, 28, 22, },
        {  6,  7,  9, 12, 20, 35, 32, 25, },
        {  7,  9, 15, 22, 27, 44, 41, 31, },
        { 10, 14, 22, 26, 32, 42, 45, 37, },
        { 20, 26, 31, 35, 41, 48, 48, 40, },
        { 29, 37, 38, 39, 45, 40, 41, 40, },
};

class QNTCodec {
public:
    QNTCodec(qtable_t quantizationTable=defaultQuantizationTable) {
        memcpy(this->quantizationTable, quantizationTable, sizeof(this->quantizationTable));
    }

    void encode(DCTImage &source, QNTImage &target);
    void decode(QNTImage &source, DCTImage &target);

private:
    qtable_t quantizationTable;
};


#endif //JPEG_QNTCODEC_H
