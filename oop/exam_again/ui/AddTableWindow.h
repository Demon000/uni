#include "../entities/TTTTable.h"
#include "../repositories/TTTTableRepository.h"
#include "../services/TTTTableService.h"

#include <QtWidgets>

#ifndef ADD_TABLE_WINDOW_H
#define ADD_TABLE_WINDOW_H

class AddTableWindow : public QWidget {
public:
	AddTableWindow(TTTTableService& service) : service{service} {
		QFormLayout* layout = new QFormLayout();
		setLayout(layout);

		QLabel* label;

		label = new QLabel("Id");
		idInput = new QSpinBox();
		layout->addRow(label, idInput);

		label = new QLabel("Size");
		sizeInput = new QSpinBox();
		sizeInput->setMinimum(3);
		sizeInput->setMaximum(5);
		layout->addRow(label, sizeInput);

		label = new QLabel("Table");
		tableInput = new QLineEdit();
		layout->addRow(label, tableInput);

		label = new QLabel("Next player");
		nextPlayerInput = new QLineEdit();
		layout->addRow(label, nextPlayerInput);

		// label = new QLabel("State");
		// stateInput = new QLineEdit();
		// layout->addRow(label, stateInput);

		QPushButton* addButton = new QPushButton("Add");
		layout->addRow(addButton);
		connect(addButton, &QPushButton::pressed, this, &AddTableWindow::createTable);
	}

	void showErrorMessage(std::string message) {
		QErrorMessage* dialog = new QErrorMessage();
		dialog->showMessage(QString::fromStdString(message));
	}

	void createTable() {
		int id = idInput->value();
		int size = sizeInput->value();
		std::string table = tableInput->text().toStdString();
		std::string nextPlayer = nextPlayerInput->text().toStdString();
		// std::string state = stateInput->text().toStdString();

		try {
			service.addTable(id, size, table, nextPlayer);
		} catch (TableExistsException&) {
			showErrorMessage("Table with this id already exists.");
		} catch (InvalidTableSizeException&) {
			showErrorMessage("Table size must be betwee 3 and 5.");
		} catch (InvalidTableException&) {
			showErrorMessage("Table format is invalid.");
		} catch (InvalidNextPlayerException&) {
			showErrorMessage("Table next player must be either X or 0.");
		} catch (InvalidTableStateException&) {
			showErrorMessage("Table state must be either 'Not started', 'In progress' or 'Finished'.");
		}
	}

private:
	TTTTableService& service;
	QSpinBox* idInput;
	QSpinBox* sizeInput;
	QLineEdit* tableInput;
	QLineEdit* nextPlayerInput;
	// QLineEdit* stateInput;
};

#endif // ADD_TABLE_WINDOW_H