#include "MainWindow.h"

MainWindow::MainWindow(ObservableTenantService& service) : service(service) {
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    table = new TenantsTable();
    layout->addWidget(table);

    QWidget* filterWidget = new QWidget();
    QHBoxLayout* filterLayout = new QHBoxLayout();
    filterWidget->setLayout(filterLayout);
    layout->addWidget(filterWidget);

    QLabel* filterLabel = new QLabel("Filter");
    filterLayout->addWidget(filterLabel);

    filterInput = new QLineEdit();
    filterInput->setClearButtonEnabled(true);
    filterLayout->addWidget(filterInput);
    connect(filterInput, &QLineEdit::textEdited,
            this, &MainWindow::refreshTenants);

    QWidget* buttonsWidget = new QWidget();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsWidget->setLayout(buttonsLayout);
    layout->addWidget(buttonsWidget);

    QPushButton* addTenantButton = new QPushButton("Add tenant");
    buttonsLayout->addWidget(addTenantButton);
    connect(addTenantButton, &QPushButton::clicked,
            this, &MainWindow::showAddTenantWindow);

    QPushButton* updateTenantButton = new QPushButton("Update tenant");
    buttonsLayout->addWidget(updateTenantButton);
    connect(updateTenantButton, &QPushButton::clicked,
            this, &MainWindow::showUpdateTenantWindow);

    QPushButton* removeTenantButton = new QPushButton("Remove tenant");
    buttonsLayout->addWidget(removeTenantButton);
    connect(removeTenantButton, &QPushButton::clicked,
            this, &MainWindow::removeTenant);

    QPushButton* notifyTenantButton = new QPushButton("Notify tenant");
    buttonsLayout->addWidget(notifyTenantButton);
    connect(notifyTenantButton, &QPushButton::clicked,
            this, &MainWindow::notifyTenant);

    QPushButton* undoButton = new QPushButton("Undo");
    buttonsLayout->addWidget(undoButton);
    connect(undoButton, &QPushButton::clicked,
            this, &MainWindow::undoAction);

    QWidget* notificationsWidget = new QWidget();
    QHBoxLayout* notificationsLayout = new QHBoxLayout();
    notificationsWidget->setLayout(notificationsLayout);
    layout->addWidget(notificationsWidget);

    QPushButton* notificationsButton = new QPushButton("Notifications");
    notificationsLayout->addWidget(notificationsButton);
    connect(notificationsButton, &QPushButton::clicked,
            this, &MainWindow::showApartmentNotificationsWindow);

    QPushButton* visualButton = new QPushButton("Visual notifications");
    notificationsLayout->addWidget(visualButton);
    connect(visualButton, &QPushButton::clicked,
            this, &MainWindow::showVisualNotificationsWindow);

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

void MainWindow::showUpdateTenantWindow() {
    int selected = table->selectedTenantNumber();
    if (selected == -1) {
        return;
    }

    UpdateTenantWindow* updateTenantWindow = new UpdateTenantWindow(service, selected);
    updateTenantWindow->show();
}

void MainWindow::showApartmentNotificationsWindow() {
    NotificationsWindow* notificationsWindow = new NotificationsWindow(service);
    notificationsWindow->show();
}

void MainWindow::showVisualNotificationsWindow() {
    VisualWindow* visualWindow = new VisualWindow(service);
    visualWindow->show();
}

void MainWindow::removeTenant() {
    int selected = table->selectedTenantNumber();
    if (selected == -1) {
        return;
    }

    try {
        service.removeTenant(selected);
    } catch (TenantMissingException&) {
        // ignore
    }
}

void MainWindow::notifyTenant() {
    int selected = table->selectedTenantNumber();
    if (selected == -1) {
        return;
    }

    try {
        service.addNotification(selected);
    } catch (NumberExistsException&) {
        // ignore
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
