#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/ExceptionRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/TenantService.h"

#ifndef GUI_H
#define GUI_H

class GUI : public QWidget {
public:
    GUI(TenantService&);
    void run();

private:
    void showErrorMessage(std::string);
    void showTenants(std::vector<Tenant>);
    void showFilteredTenants(std::string);
    void refreshTenants();
    int getSelectedTenantNumber();
    void showAddTenantWindow();
    void showUpdateTenantWindow(int);

    TenantService& service;
    QTableWidget* table;
};

#endif // GUI_H
