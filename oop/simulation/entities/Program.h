#include <string>

#ifndef PROGRAM_H
#define PROGRAM_H

class Program {
public:
    Program(std::string, std::string, std::string, int);
    std::string getTitle() const;
    std::string getChannel() const;
    std::string getDay() const;
    int getHour() const;

private:
    std::string title;
    std::string channel;
    std::string day;
    int hour;
};

#endif // PROGRAM_H
