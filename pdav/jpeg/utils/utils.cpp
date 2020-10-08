#include <cstdint>
#include <algorithm>
#include "utils.h"

uint8_t clampByte(double x) {
    return std::clamp(x, 0.0, 255.0);
}

