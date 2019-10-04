#include "../entities/TTTTable.h"
#include "../repositories/TTTTableRepository.h"
#include "../services/TTTTableService.h"

#include "AddTableWindow.h"

#include <QtWidgets>

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

class MainWindow : public QWidget, public Observer {
public:
	MainWindow(TTTTableService& service) : service{service} {
		QVBoxLayout* layout = new QVBoxLayout();
		setLayout(layout);

		table = new QTableWidget();
		layout->addWidget(table);

		table->setColumnCount(5);
		table->setEditTriggers(QAbstractItemView::NoEditTriggers);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->verticalHeader()->hide();
		table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		table->setHorizontalHeaderLabels(QStringList{"Id", "Size", "Table", "Next player", "State"});

		QWidget* buttonsWidget = new QWidget();
		layout->addWidget(buttonsWidget);

		QHBoxLayout* buttonsLayout = new QHBoxLayout();
		buttonsWidget->setLayout(buttonsLayout);

		QPushButton* addTableButton = new QPushButton("Add table");
		buttonsLayout->addWidget(addTableButton);
		connect(addTableButton, &QPushButton::pressed, this, &MainWindow::createAddTableWindow);

		service.subscribe(this);
		refresh();
	}

	void createAddTableWindow() {
		AddTableWindow* addTableWindow = new AddTableWindow(service);
		addTableWindow->show();
	}

	void refresh() {
		std::vector<TTTTable> ttttables = service.getTables();

		table->setRowCount(ttttables.size());

		int row = 0;
		for (const TTTTable& ttttable : ttttables) {
			QTableWidgetItem* item;

			item = new QTableWidgetItem(QString::number(ttttable.getId()));
			table->setItem(row, 0, item);

			item = new QTableWidgetItem(QString::number(ttttable.getSize()));
			table->setItem(row, 1, item);

			item = new QTableWidgetItem(QString::fromStdString(ttttable.getTable()));
			table->setItem(row, 2, item);

			item = new QTableWidgetItem(QString::fromStdString(ttttable.getNextPlayer()));
			table->setItem(row, 3, item);

			item = new QTableWidgetItem(QString::fromStdString(ttttable.getState()));
			table->setItem(row, 4, item);

			row++;
		}
	}

	void receive(ObserveEvent event) {
		if (event != ObserveEvent::CHANGE) {
			return;
		}

		refresh();
	}

	~MainWindow() {
		service.unsubscribe(this);
	}

private:
	TTTTableService& service;
	QTableWidget *table;
};

#endif // MAIN_WINDOW_H
