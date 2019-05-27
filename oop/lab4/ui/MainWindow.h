#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/ObservableTenantService.h"
#include "../ui/CommonWindow.h"

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

class MainWindow : public QWidget, public CommonWindow, public Observer {
public:
    MainWindow(ObservableTenantService&);

private:
    void showTenants(std::vector<Tenant>);
    void showFilteredTenants(std::string);
    void refreshTenants();

    int getSelectedTenantNumber();
    void showAddTenantWindow();
    void showUpdateTenantWindow(int);
    void removeTenant(int);
    void undoAction();

    void receive(ObserveEvent) override;

    ObservableTenantService& service;
    QTableWidget* table;
};

#endif // MAIN_WINDOW_H
