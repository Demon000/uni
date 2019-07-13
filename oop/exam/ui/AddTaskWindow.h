#include <sstream>

#include "../services/TaskService.h"
#include "../observe/Observe.h"

#include <QtWidgets>

class AddTaskWindow : public QWidget {
public:
    AddTaskWindow(TaskService& service) : service{service} {
        QFormLayout* layout = new QFormLayout();
        setLayout(layout);

        QLabel* label;

        label = new QLabel("Id");
        idInput = new QSpinBox();
        layout->addRow(label, idInput);

        label = new QLabel("Description");
        descriptionInput = new QLineEdit();
        layout->addRow(label, descriptionInput);

        label = new QLabel("State");
        stateInput = new QLineEdit();
        layout->addRow(label, stateInput);

        label = new QLabel("Programmers");
        programmersInput = new QTextEdit();
        layout->addRow(label, programmersInput);

        QPushButton* addButton = new QPushButton("Add task");
        layout->addWidget(addButton);
        connect(addButton, &QPushButton::pressed, this, &AddTaskWindow::addTask);
    }

    void showErrorMessage(std::string message) {
        QErrorMessage* dialog = new QErrorMessage();
        dialog->showMessage(QString::fromStdString(message));
    }

    void addTask() {
        int id = idInput->value();
        std::string description = descriptionInput->text().toStdString();
        std::string state = stateInput->text().toStdString();
        std::string data = programmersInput->toPlainText().toStdString();
        std::vector<std::string> programmers;

        std::stringstream ss(data);
        std::string word;

        while(getline(ss, word)) {
            programmers.push_back(word);
        }

        try {
            service.addTask(id, description, state, programmers);
        } catch (TaskExists&) {
            showErrorMessage("Task already exists.");
        } catch (TaskDescriptionMissing&) {
            showErrorMessage("Task description cannot be empty.");
        } catch (TaskStateWrong&) {
            showErrorMessage("Task state can only be open, closed, or inprogress.");
        } catch (TaskProgrammersNumberWrong&) {
            showErrorMessage("Task number of programmers must be min 1 and max 4.");
        }
    }

private:
    TaskService& service;
    QSpinBox* idInput;
    QLineEdit* descriptionInput;
    QLineEdit* stateInput;
    QTextEdit* programmersInput;
};
