#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../services/ObservableTenantService.h"
#include "CommonWindow.h"

#ifndef UPDATE_TENANT_WINDOW_H
#define UPDATE_TENANT_WINDOW_H

class UpdateTenantWindow : public QWidget, public CommonWindow {
public:
    UpdateTenantWindow(ObservableTenantService&, int);

private:
    void updateTenant();


    ObservableTenantService& service;
    int selected;
    QLineEdit* nameInput;
};

#endif // UPDATE_TENANT_WINDOW_H
