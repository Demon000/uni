#include <vector>

#include "../entities/Program.h"
#include "../repositories/ProgramRepository.h"

#ifndef PROGRAM_SERVICE_H
#define PROGRAM_SERVICE_H

class ProgramService {
public:
    ProgramService(ProgramRepository&);

    std::vector<Program> getPrograms();
    std::vector<Program> getProgramsSortedByTitle();
    std::vector<Program> getProgramsSortedByDay();

private:
    ProgramRepository& repository;
};

#endif // PROGRAM_SERVICE_H
