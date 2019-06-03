#include "NotificationsWindow.h"

NotificationsWindow::NotificationsWindow(ObservableTenantService& service)
        : service{service} {
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    table = new TenantsTable();
    layout->addWidget(table);

    QWidget* generateWidget = new QWidget();
    QHBoxLayout* generateLayout = new QHBoxLayout();
    generateWidget->setLayout(generateLayout);
    layout->addWidget(generateWidget);

    QLabel* numberLabel = new QLabel("Apartments");
    generateLayout->addWidget(numberLabel);

    numberInput = new QSpinBox();
    numberInput->setMinimum(1);
    generateLayout->addWidget(numberInput);

    QPushButton* generateButton = new QPushButton("Generate apartments");
    generateLayout->addWidget(generateButton);
    connect(generateButton, &QPushButton::clicked,
            this, &NotificationsWindow::generateNotifiedApartments);

    QPushButton* deleteButton = new QPushButton("Delete apartments");
    layout->addWidget(deleteButton);
    connect(deleteButton, &QPushButton::clicked,
            this, &NotificationsWindow::deleteNotifiedApartments);

    refreshTenants();
    service.subscribe(this);
}

void NotificationsWindow::receive(ObserveEvent event) {
    switch (event) {
    case ObserveEvent::CHANGE:
        refreshTenants();
        break;
    default:
        break;
    }
}

void NotificationsWindow::generateNotifiedApartments() {
    int number = numberInput->value();
    service.addRandomNotifications(number);
}

void NotificationsWindow::deleteNotifiedApartments() {
    service.removeNotifications();
}

void NotificationsWindow::refreshTenants() {
    std::vector<Tenant> tenants = service.getTenantsToNotify();
    table->showTenants(tenants);
}
