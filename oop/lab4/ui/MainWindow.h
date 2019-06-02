#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/ObservableTenantService.h"

#include "CommonWindow.h"
#include "TenantsTable.h"

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

class MainWindow : public QWidget, public CommonWindow, public Observer {
public:
    MainWindow(ObservableTenantService&);

private:
    void refreshTenants();

    int getSelectedTenantNumber();
    void showAddTenantWindow();
    void showUpdateTenantWindow();
    void removeTenant();
    void undoAction();

    void receive(ObserveEvent) override;

    ObservableTenantService& service;
    TenantsTable* table;
    QLineEdit* filterInput;
};

#endif // MAIN_WINDOW_H
