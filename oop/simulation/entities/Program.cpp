#include <string>

#include "Program.h"

Program::Program(std::string title, std::string channel, std::string day, int hour) :
    title{title}, channel{channel}, day{day}, hour{hour} {}

std::string Program::getTitle() const {
    return title;
}

std::string Program::getChannel() const {
    return channel;
}

std::string Program::getDay() const {
    return day;
}

int Program::getHour() const {
    return hour;
}
