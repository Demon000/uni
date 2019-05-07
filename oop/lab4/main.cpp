#include "repositories/TenantRepository.h"
#include "services/TenantService.h"
#include "ui/Console.h"

int main() {
    TenantRepository repository{"tenants.csv"};
    NotificationRepository notificationRepository{"notifications.csv"};

    TenantService service{repository, notificationRepository};

    Console console{service};
    console.run();

    return 0;
}
