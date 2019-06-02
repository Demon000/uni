#include "UpdateTenantWindow.h"

UpdateTenantWindow::UpdateTenantWindow(ObservableTenantService& service,
        int selected) : service{service}, selected{selected} {
    QVBoxLayout* layout = new QVBoxLayout();
    setLayout(layout);

    QWidget* fieldsWidget = new QWidget();
    QFormLayout* fieldsLayout = new QFormLayout();
    fieldsWidget->setLayout(fieldsLayout);

    QLabel* nameLabel = new QLabel(QString("Name"));
    nameInput = new QLineEdit();
    fieldsLayout->addRow(nameLabel, nameInput);
    layout->addWidget(fieldsWidget);

    QPushButton* updateButton = new QPushButton("Update");
    layout->addWidget(updateButton);
    connect(updateButton, &QPushButton::clicked, this, &UpdateTenantWindow::updateTenant);
}

void UpdateTenantWindow::updateTenant() {
    std::string name = nameInput->text().toStdString();

    if (!name.length()) {
        showErrorMessage("Tenant name cannot be empty.");
        return;
    }

    try {
        service.updateTenant(selected, name);
    } catch (TenantMissingException&) {
        showErrorMessage("Tenant does not exist.");
    }
}
