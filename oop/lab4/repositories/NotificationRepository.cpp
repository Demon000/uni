#include <algorithm>
#include <fstream>

#include "NotificationRepository.h"

using std::string;
using std::vector;
using std::find;
using std::ifstream;
using std::ofstream;

NotificationRepository::NotificationRepository(const string& path) : path(path) {
    readNumbers();
}

void NotificationRepository::readNumbers() {
    numbers.clear();

    ifstream in(path);

    int number;

    if (!in.good()) {
        in.close();
        writeNumbers();
    }

    while (in >> number) {
        numbers.push_back(number);
    }
}

void NotificationRepository::writeNumbers() const {
    ofstream out(path);

    for (const int& number : numbers) {
        out << number << "\n";
    }
}

void NotificationRepository::addNumber(int number) {
    readNumbers();

    numbers.push_back(number);

    writeNumbers();
}

void NotificationRepository::numberExists(int number) {
    readNumbers();

    auto it = find(numbers.begin(), numbers.end(), number);
    if (it == numbers.end()) {
        throw NumberMissingException();
    }
}

vector<int> NotificationRepository::getNumbers() {
    readNumbers();

    return numbers;
}

void NotificationRepository::removeNumber(int number) {
    readNumbers();

    auto it = find(numbers.begin(), numbers.end(), number);
    if (it == numbers.end()) {
        throw NumberMissingException();
    }

    numbers.erase(it);

    writeNumbers();
}

void NotificationRepository::removeNumbers() {
    numbers.clear();

    writeNumbers();
}
