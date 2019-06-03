#include <string>
#include <vector>

#include <QtWidgets>

#include "../entities/Tenant.h"
#include "../services/ObservableTenantService.h"
#include "../observe/Observe.h"

#include "CommonWindow.h"
#include "TenantsTable.h"

#ifndef VISUAL_WINDOW_H
#define VISUAL_WINDOW_H

class VisualWindow : public QWidget, public CommonWindow, public Observer {
public:
    VisualWindow(ObservableTenantService&);
    void refreshShapes();

private:

    int getIntInRange(int start, int end);
    void drawShape();
    void paintEvent(QPaintEvent* ev) override;
    void receive(ObserveEvent) override;

    ObservableTenantService& service;
    QSpinBox* numberInput;
};

#endif // VISUAL_WINDOW_H
