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

vector<int> NotificationRepository::readNumbers() const {
    vector<int> numbers;
    ifstream in(path);

    int number;

    if (!in) {
        writeNumbers(numbers);
    }

    while (in >> number) {
        numbers.push_back(number);
    }

    return numbers;
}

void NotificationRepository::writeNumbers(const vector<int>& numbers) const {
    ofstream out(path);

    for (const int& number : numbers) {
        out << number << "\n";
    }
}

void NotificationRepository::addNumber(int number) const {
    vector<int> numbers = readNumbers();
    numbers.push_back(number);
    writeNumbers(numbers);
}

void NotificationRepository::numberExists(int number) const {
    vector<int> numbers = readNumbers();
    auto it = find(numbers.begin(), numbers.end(), number);
    if (it == numbers.end()) {
        throw NumberMissingException();
    }
}

vector<int> NotificationRepository::getNumbers() const {
    vector<int> numbers = readNumbers();
    return numbers;
}

void NotificationRepository::removeNumber(int number) const {
    vector<int> numbers = readNumbers();
    auto it = find(numbers.begin(), numbers.end(), number);
    if (it == numbers.end()) {
        throw NumberMissingException();
    }

    numbers.erase(it);
    writeNumbers(numbers);
}

void NotificationRepository::removeNumbers() const {
    vector<int> numbers = readNumbers();
    numbers.clear();
    writeNumbers(numbers);
}
