#include <algorithm>

#include "NotificationRepository.h"

using std::vector;
using std::find;

void NotificationRepository::addNumber(int number) {
    numbers.push_back(number);
}

void NotificationRepository::getTenantByNumber(int number) {
    auto it = find(numbers.begin(), numbers.end(), number);
    if (it == numbers.end()) {
        throw NumberMissingException();
    }
}

vector<int>& NotificationRepository::getNumbers() {
    return numbers;
}

void NotificationRepository::removeNumber(int number) {
    auto it = find(numbers.begin(), numbers.end(), number);
    if (it == numbers.end()) {
        throw NumberMissingException();
    }

    numbers.erase(it);
}

void NotificationRepository::removeNumbers() {
    numbers.clear();
}
