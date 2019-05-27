#include "AddTenantWindow.h"

AddTenantWindow::AddTenantWindow(ObservableTenantService& service)
        : service{service} {
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    QWidget* fieldsWidget = new QWidget();
    QFormLayout* fieldsLayout = new QFormLayout();
    fieldsWidget->setLayout(fieldsLayout);
    layout->addWidget(fieldsWidget);

    QLabel* numberLabel = new QLabel(QString("Number"));
    numberInput = new QSpinBox();
    numberInput->setMinimum(1);
    fieldsLayout->addRow(numberLabel, numberInput);

    QLabel* nameLabel = new QLabel(QString("Name"));
    nameInput = new QLineEdit();
    fieldsLayout->addRow(nameLabel, nameInput);

    QLabel* surfaceLabel = new QLabel(QString("Surface"));
    surfaceInput = new QSpinBox();
    surfaceInput->setMinimum(1);
    fieldsLayout->addRow(surfaceLabel, surfaceInput);

    QLabel* typeLabel = new QLabel(QString("Type"));
    typeInput = new QLineEdit();
    fieldsLayout->addRow(typeLabel, typeInput);

    QPushButton* addButton = new QPushButton("Add");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &AddTenantWindow::addTenant);
}

void AddTenantWindow::addTenant() {
    int number = numberInput->value();
    std::string name = nameInput->text().toStdString();
    int surface = surfaceInput->value();
    std::string type = typeInput->text().toStdString();

    if (!name.length()) {
        showErrorMessage("Tenant name cannot be empty.");
        return;
    }

    if (!type.length()) {
        showErrorMessage("Apartment type cannot be empty.");
        return;
    }

    try {
        service.createTenant(number, name, surface, type);
    } catch (TenantExistsException&) {
        showErrorMessage("Tenant already exists.");
    }
}
