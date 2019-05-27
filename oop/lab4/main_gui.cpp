#include "repositories/TenantRepository.h"
#include "services/ObservableTenantService.h"
#include "ui/GUI.h"

#include <QApplication>

int main(int argc, char **argv) {
    TenantRepository repository{"tenants.csv"};
    NotificationRepository notificationRepository{"notifications.csv"};

    ObservableTenantService service{repository, notificationRepository};

    QApplication app(argc, argv);

    GUI gui{service};
    gui.show();

    return app.exec();
}
