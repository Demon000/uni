#include "../services/TaskService.h"
#include "../observe/Observe.h"

#include "AddTaskWindow.h"

#include <QtWidgets>

class MainWindow : public QWidget, public Observer {
public:
    MainWindow(TaskService& service) : service{service} {
        QVBoxLayout* layout = new QVBoxLayout();
        setLayout(layout);

        table = new QTableWidget();
        layout->addWidget(table);
        table->setColumnCount(4);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->verticalHeader()->hide();
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->setHorizontalHeaderLabels(QStringList{"Id", "Desription", "Status", "Number of programmers"});

        QLabel* filterLabel = new QLabel("Filter");
        layout->addWidget(filterLabel);

        filterInput = new QLineEdit();
        layout->addWidget(filterInput);
        connect(filterInput, &QLineEdit::textEdited, this, &MainWindow::refreshTasks);

        QPushButton* addTaskButton = new QPushButton("Add task");
        layout->addWidget(addTaskButton);
        connect(addTaskButton, &QPushButton::pressed, this, &MainWindow::addTask);


        refreshTasks();
        service.subscribe(this);
    }

    void addTask() {
        AddTaskWindow* addTaskWindow = new AddTaskWindow(service);
        addTaskWindow->show();
    }

    void receive(ObserveEvent event) {
        if (event == ObserveEvent::CHANGE) {
            refreshTasks();
        }
    }

    void refreshTasks() {
        std::vector<Task> tasks;
        std::string text = filterInput->text().toStdString();

        if (text == "") {
            tasks = service.getTasks();
        } else {
            tasks = service.getFilteredTasks(text);
        }
        table->setRowCount(tasks.size());

        int row = 0;
        for (const Task& task : tasks) {
            QTableWidgetItem* item;

            item = new QTableWidgetItem(QString::number(task.getId()));
            table->setItem(row, 0, item);

            item = new QTableWidgetItem(QString::fromStdString(task.getDescription()));
            table->setItem(row, 1, item);

            item = new QTableWidgetItem(QString::fromStdString(task.getState()));
            table->setItem(row, 2, item);

            item = new QTableWidgetItem(QString::number(task.getNumberOfProgrammers()));
            table->setItem(row, 3, item);

            row++;
        }
    }

private:
    TaskService& service;
    QTableWidget* table;
    QLineEdit* filterInput;
};
