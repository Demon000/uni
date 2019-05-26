#include <vector>

#include <QWidget>
#include <QListWidget>

#include "../entities/Program.h"
#include "../repositories/ProgramRepository.h"
#include "../services/ProgramService.h"

class GUI : public QWidget {
public:
    GUI(ProgramService&);
    void showPrograms(std::vector<Program>);
	void showProgramsSimple();
	void showProgramsSortedByTitle();
	void showProgramsSortedByDay();

private:
    ProgramService& service;
    QListWidget* list;
};
