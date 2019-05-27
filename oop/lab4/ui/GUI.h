#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/ExceptionRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/ObservableTenantService.h"

#ifndef GUI_H
#define GUI_H

class GUI : public QWidget {
public:
    GUI(ObservableTenantService&);
    void run();

private:
    void showErrorMessage(std::string);
    void showTenants(std::vector<Tenant>);
    void showFilteredTenants(std::string);
    void refreshTenants();
    int getSelectedTenantNumber();
    void showAddTenantWindow();
    void showUpdateTenantWindow(int);

    ObservableTenantService& service;
    QTableWidget* table;
};

#endif // GUI_H
