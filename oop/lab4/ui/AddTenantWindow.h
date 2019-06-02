#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../services/ObservableTenantService.h"

#include "CommonWindow.h"

#ifndef ADD_TENANT_WINDOW_H
#define ADD_TENANT_WINDOW_H

class AddTenantWindow : public QWidget, public CommonWindow {
public:
    AddTenantWindow(ObservableTenantService&);

private:
    void addTenant();

    ObservableTenantService& service;
    QSpinBox* numberInput;
    QLineEdit* nameInput;
    QSpinBox* surfaceInput;
    QLineEdit* typeInput;
};

#endif // ADD_TENANT_WINDOW_H
