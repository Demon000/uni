#include <vector>
#include <string>

#include "GUI.h"

GUI::GUI(ProgramService& service) : service{service} {
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    list = new QListWidget();
    layout->addWidget(list);

    QWidget* buttonsWidget = new QWidget();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsWidget->setLayout(buttonsLayout);

    QPushButton* sortByTitleButton = new QPushButton("Sort by title");
    buttonsLayout->addWidget(sortByTitleButton);
    connect(sortByTitleButton, &QPushButton::clicked, [&]() {
        showProgramsSortedByTitle();
    });

    QPushButton* sortByDayButton = new QPushButton("Sort by day");
    buttonsLayout->addWidget(sortByDayButton);
    connect(sortByDayButton, &QPushButton::clicked, [&]() {
        showProgramsSortedByDay();
    });

    layout->addWidget(buttonsWidget);
    showProgramsSimple();
}

void GUI::showPrograms(std::vector<Program> programs) {
    list->clear();
    for (const Program& program : programs) {
        std::string message = program.getTitle() + " - " + program.getChannel() + ", " + program.getDay();
        //qDebug(message.c_str());
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(message));
        if (program.getChannel() == "Paprika") {
            item->setBackgroundColor(Qt::red);
        }
        list->addItem(item);
    }
    //qDebug("\n");
}

void GUI::showProgramsSimple() {
    std::vector<Program> programs = service.getPrograms();
    showPrograms(programs);
}

void GUI::showProgramsSortedByTitle() {
    std::vector<Program> programs = service.getProgramsSortedByTitle();
    showPrograms(programs);
}

void GUI::showProgramsSortedByDay() {
    std::vector<Program> programs = service.getProgramsSortedByDay();
    showPrograms(programs);
}
