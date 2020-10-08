#include <cassert>
#include "QNTCodec.h"
#include "../generic/Int32Image.h"

void QNTCodec::encode(Int32Image &source, Int32Image &target) {
    assert(source.type == Int32ImageType::INT32_DCT);
}

void QNTCodec::decode(Int32Image &source, Int32Image &target) {
    assert(source.type == Int32ImageType::INT32_QNT);

}
