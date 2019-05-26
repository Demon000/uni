#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "ProgramRepository.h"

ProgramRepository::ProgramRepository(std::string path) : path{path} {}

std::vector<Program> ProgramRepository::readPrograms() {
    std::vector<Program> programs;
    std::vector<std::string> words;
    std::string word, line;

    std::ifstream in(path);

    std::string title;
    std::string channel;
    std::string day;
    int hour;

   while(getline(in, line)) {
        std::stringstream ss(line);
        while(getline(ss, word, ',')) {
             words.push_back(word);
        }
   }

    for (auto it = words.begin(); it < words.end(); it += 4) {
        title = it[0];
        channel = it[1];
        day = it[2];
        hour = std::stoi(it[3]);

        Program program{title, channel, day, hour};
        programs.push_back(program);
    }

    return programs;
}

std::vector<Program> ProgramRepository::getPrograms() {
    std::vector<Program> programs = readPrograms();
    return programs;
}
