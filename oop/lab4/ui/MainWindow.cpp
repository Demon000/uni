#include "MainWindow.h"
#include "AddTenantWindow.h"

MainWindow::MainWindow(ObservableTenantService& service) : service(service) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    table = new QTableWidget();
    table->setColumnCount(5);
    mainLayout->addWidget(table);

    table->setSortingEnabled(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    table->verticalHeader()->hide();
    table->setHorizontalHeaderLabels(QStringList{"Number", "Name", "Surface", "Type", "Same surface"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QWidget* filterWidget = new QWidget();
    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterWidget->setLayout(filterLayout);
    mainLayout->addWidget(filterWidget);

    QLabel* filterLabel = new QLabel("Filter");
    filterLayout->addWidget(filterLabel);

    QLineEdit* filterInput = new QLineEdit();
    filterInput->setClearButtonEnabled(true);
    filterLayout->addWidget(filterInput);
    connect(filterInput, &QLineEdit::textEdited, [&](QString text) {
        showFilteredTenants(text.toStdString());
    });

    QWidget* buttonsWidget = new QWidget();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsWidget->setLayout(buttonsLayout);
    mainLayout->addWidget(buttonsWidget);

    QPushButton* addTenantButton = new QPushButton("Add tenant");
    buttonsLayout->addWidget(addTenantButton);
    connect(addTenantButton, &QPushButton::clicked, [&]() {
        showAddTenantWindow();
    });

    QPushButton* updateTenantButton = new QPushButton("Update tenant");
    buttonsLayout->addWidget(updateTenantButton);
    connect(updateTenantButton, &QPushButton::clicked, [&]() {
        int selected = getSelectedTenantNumber();
        if (selected == -1) {
            return;
        }

        showUpdateTenantWindow(selected);
    });

    QPushButton* removeTenantButton = new QPushButton("Remove tenant");
    buttonsLayout->addWidget(removeTenantButton);
    connect(removeTenantButton, &QPushButton::clicked, [&]() {
        int selected = getSelectedTenantNumber();
        if (selected == -1) {
            return;
        }

        try {
            service.removeTenant(selected);
        } catch (TenantMissingException&) {
            showErrorMessage("Tenant does not exist.");
        }
    });

    QPushButton* undoButton = new QPushButton("Undo");
    buttonsLayout->addWidget(undoButton);
    connect(undoButton, &QPushButton::clicked, [&]() {
        try {
            service.undo();
        } catch (NoUndoActions&) {
            showErrorMessage("No undo actions left.");
        }
    });

    service.onChanged([&]() {
        refreshTenants();
    });
    refreshTenants();
}

int MainWindow::getSelectedTenantNumber() {
    QList<QTableWidgetItem*> items = table->selectedItems();

    for (QTableWidgetItem* item : items) {
        if (item->column() == 0) {
            QString text = item->text();
            int number = text.toInt();
            return number;
        }
    }

    return -1;
}

void MainWindow::showAddTenantWindow() {
    AddTenantWindow* addTenantWindow = new AddTenantWindow(service);
    addTenantWindow->show();
}

void MainWindow::showUpdateTenantWindow(int selected) {
    QWidget* window = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    window->setLayout(layout);

    QWidget* fieldsWidget = new QWidget();
    QFormLayout* fieldsLayout = new QFormLayout();
    fieldsWidget->setLayout(fieldsLayout);

    QLabel* nameLabel = new QLabel(QString("Name"));
    QLineEdit* nameInput = new QLineEdit();
    fieldsLayout->addRow(nameLabel, nameInput);
    layout->addWidget(fieldsWidget);

    QPushButton* updateButton = new QPushButton("Update");
    layout->addWidget(updateButton);
    connect(updateButton, &QPushButton::clicked, [=]() {
        std::string name = nameInput->text().toStdString();

        try {
            service.updateTenant(selected, name);
        } catch (TenantMissingException&) {
            showErrorMessage("Tenant does not exist.");
        }
    });

    window->show();
}

void MainWindow::showTenants(std::vector<Tenant> tenants) {
    std::unordered_map<int, int> surfaceReport = service.getSurfaceReport();

    int rows = tenants.size();
    table->setRowCount(rows);

    QBrush background;
    if (rows < 5) {
        background = Qt::red;
    }

    int row = 0;
    for (const Tenant& tenant : tenants) {
        QTableWidgetItem* item;
        QString text;

        text = QString::number(tenant.getNumber());
        item = new QTableWidgetItem(text);
        item->setBackground(background);
        table->setItem(row, 0, item);

        text = QString::fromStdString(tenant.getName());
        item = new QTableWidgetItem(text);
        item->setBackground(background);
        table->setItem(row, 1, item);

        text = QString::number(tenant.getSurface());
        item = new QTableWidgetItem(text);
        item->setBackground(background);
        table->setItem(row, 2, item);

        text = QString::fromStdString(tenant.getType());
        item = new QTableWidgetItem(text);
        item->setBackground(background);
        table->setItem(row, 3, item);

        text = QString::number(surfaceReport[tenant.getSurface()]);
        item = new QTableWidgetItem(text);
        item->setBackground(background);
        table->setItem(row, 4, item);

        row++;
    }
}

void MainWindow::refreshTenants() {
    std::vector<Tenant> tenants = service.getTenants();
    showTenants(tenants);

}

void MainWindow::showFilteredTenants(std::string text) {
    std::vector<Tenant> tenants = service.getFilteredTenants(text);
    showTenants(tenants);
}
