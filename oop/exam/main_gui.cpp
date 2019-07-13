#include "repositories/TaskRepository.h"
#include "services/TaskService.h"
#include "ui/MainWindow.h"

#include <QApplication>

int main(int argc, char **argv) {
    TaskRepository repository{"tasks.csv"};
    TaskValidator validator;
    TaskService service{repository, validator};

    QApplication app(argc, argv);

    MainWindow mainWindow{service};
    mainWindow.show();

    return app.exec();
}
