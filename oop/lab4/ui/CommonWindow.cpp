#include "CommonWindow.h"

void CommonWindow::showErrorMessage(std::string message) {
    QErrorMessage* dialog = new QErrorMessage();
    dialog->showMessage(QString::fromStdString(message));
}
