#include "repositories/ProgramRepository.h"
#include "services/ProgramService.h"
#include "ui/GUI.h"

#include <QApplication>

int main(int argc, char **argv) {
    ProgramRepository repository{"programs.csv"};
    ProgramService service{repository};

    QApplication app(argc, argv);

    GUI gui{service};
    gui.show();

    return app.exec();
}
