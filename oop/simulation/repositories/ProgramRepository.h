#include <vector>
#include <string>

#include "../entities/Program.h"

#ifndef PROGRAM_REPOSITORY_H
#define PROGRAM_REPOSITORY_H

class ProgramRepository {
public:
    ProgramRepository(std::string);
    std::vector<Program> getPrograms();

private:
    std::vector<Program> readPrograms();

    std::string path;
};

#endif // PROGRAM_REPOSITORY_H
