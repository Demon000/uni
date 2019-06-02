#include "MainWindow.h"
#include "AddTenantWindow.h"
#include "UpdateTenantWindow.h"

MainWindow::MainWindow(ObservableTenantService& service) : service(service) {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    table = new TenantsTable(service);
    mainLayout->addWidget(table);

    QWidget* filterWidget = new QWidget();
    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterWidget->setLayout(filterLayout);
    mainLayout->addWidget(filterWidget);

    QLabel* filterLabel = new QLabel("Filter");
    filterLayout->addWidget(filterLabel);

    filterInput = new QLineEdit();
    filterInput->setClearButtonEnabled(true);
    filterLayout->addWidget(filterInput);
    connect(filterInput, &QLineEdit::textEdited, [&]() {
        refreshTenants();
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
        int selected = table->selectedTenantNumber();
        showUpdateTenantWindow(selected);
    });

    QPushButton* removeTenantButton = new QPushButton("Remove tenant");
    buttonsLayout->addWidget(removeTenantButton);
    connect(removeTenantButton, &QPushButton::clicked, [&]() {
        int selected = table->selectedTenantNumber();
        removeTenant(selected);
    });

    QPushButton* undoButton = new QPushButton("Undo");
    buttonsLayout->addWidget(undoButton);
    connect(undoButton, &QPushButton::clicked, [&]() {
        undoAction();
    });

    refreshTenants();
    service.subscribe(this);
}

void MainWindow::receive(ObserveEvent event) {
    switch (event) {
    case ObserveEvent::CHANGE:
        refreshTenants();
        break;
    default:
        break;
    }
}

void MainWindow::showAddTenantWindow() {
    AddTenantWindow* addTenantWindow = new AddTenantWindow(service);
    addTenantWindow->show();
}

void MainWindow::showUpdateTenantWindow(int selected) {
    if (selected == -1) {
        return;
    }

    UpdateTenantWindow* updateTenantWindow = new UpdateTenantWindow(service, selected);
    updateTenantWindow->show();
}

void MainWindow::removeTenant(int selected) {
    if (selected == -1) {
        return;
    }

    try {
        service.removeTenant(selected);
    } catch (TenantMissingException&) {
        showErrorMessage("Tenant does not exist.");
    }
}

void MainWindow::undoAction() {
    try {
        service.undo();
    } catch (NoUndoActions&) {
        showErrorMessage("No undo actions left.");
    }

}

void MainWindow::refreshTenants() {
    QString qs = filterInput->text();
    std::string text = qs.toStdString();

    std::vector<Tenant> tenants;
    if (text.length()) {
        tenants = service.getFilteredTenants(text);
    } else {
        tenants = service.getTenants();
    }

    table->showTenants(tenants);
}
