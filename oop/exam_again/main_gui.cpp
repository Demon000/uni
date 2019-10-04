#include "repositories/TTTTableRepository.h"
#include "services/TTTTableService.h"
#include "ui/MainWindow.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    TTTTableRepository repository{"tables.csv"};
    TTTTableValidator validator;
    TTTTableService service{repository, validator};

    MainWindow mainWindow{service};
    mainWindow.show();

    return app.exec();
}
