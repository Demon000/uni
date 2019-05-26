#include <vector>
#include <algorithm>

#include "ProgramService.h"

ProgramService::ProgramService(ProgramRepository& repository)
        : repository{repository} {}

std::vector<Program> ProgramService::getPrograms() {
    return repository.getPrograms();
}

std::vector<Program> ProgramService::getProgramsSortedByTitle() {
    std::vector<Program> programs = repository.getPrograms();

    std::sort(programs.begin(), programs.end(), [](const Program& first, const Program& second) {
        return first.getTitle() < second.getTitle();
    });

    return programs;
}

std::vector<Program> ProgramService::getProgramsSortedByDay() {
    std::vector<Program> programs = repository.getPrograms();

    std::sort(programs.begin(), programs.end(), [](const Program& first, const Program& second) {
        return first.getDay() < second.getDay();
    });

    return programs;
}
