#ifndef LAB2_UTILS_H
#define LAB2_UTILS_H

#include <string>

bool isValidDigit(char c, bool starting=false);
bool isValidIntConstant(const std::string& buffer, size_t pos=0, bool checkStarting=false);

#endif //LAB2_UTILS_H
