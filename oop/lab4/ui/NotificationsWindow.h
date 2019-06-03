#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../services/ObservableTenantService.h"
#include "../observe/Observe.h"

#include "CommonWindow.h"
#include "TenantsTable.h"

#ifndef NOTIFICATIONS_WINDOW_H
#define NOTIFICATIONS_WINDOW_H

class NotificationsWindow : public QWidget, public CommonWindow, public Observer {
public:
    NotificationsWindow(ObservableTenantService&);

private:
    void generateNotifiedApartments();
    void deleteNotifiedApartments();
    void refreshTenants();

    void receive(ObserveEvent) override;

    ObservableTenantService& service;
    TenantsTable* table;
    QSpinBox* numberInput;
};

#endif // NOTIFICATIONS_WINDOW_H
