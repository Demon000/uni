#include <vector>
#include <string>
#include <cassert>

#include "entities/Program.h"
#include "repositories/ProgramRepository.h"
#include "services/ProgramService.h"

void test_program() {
    Program program{"ProMotor", "ProTv", "sambata", 13};
    assert(program.getTitle() == "ProMotor");
    assert(program.getChannel() == "ProTv");
    assert(program.getDay() == "sambata");
    assert(program.getHour() == 13);
}

void test_program_repository() {
    ProgramRepository repository("programs_test_first.csv");
    std::vector<Program> programs = repository.getPrograms();
    assert(programs.size() == 3);
    assert(programs[0].getTitle() == "Vremea");
    assert(programs[1].getTitle() == "Stiri");
    assert(programs[2].getTitle() == "ProMotor");
}

void test_program_service() {
    ProgramRepository repository("programs_test_first.csv");
    ProgramService service(repository);
    std::vector<Program> programs;

    programs = service.getPrograms();
    assert(programs.size() == 3);
    assert(programs[0].getTitle() == "Vremea");
    assert(programs[1].getTitle() == "Stiri");
    assert(programs[2].getTitle() == "ProMotor");

    programs = service.getProgramsSortedByTitle();
    assert(programs.size() == 3);
    assert(programs[0].getTitle() == "ProMotor");
    assert(programs[1].getTitle() == "Stiri");
    assert(programs[2].getTitle() == "Vremea");

    programs = service.getProgramsSortedByDay();
    assert(programs.size() == 3);
    assert(programs[0].getDay() == "luni");
    assert(programs[1].getDay() == "marti");
    assert(programs[2].getDay() == "sambata");
}

int main() {
    test_program();
    test_program_repository();
    test_program_service();

    return 0;
}
