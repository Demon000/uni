#include "repositories/TenantRepository.h"
#include "services/TenantService.h"
#include "ui/Console.h"

int main() {
    //TenantRepository repository{"tenants.csv"};
    ExceptionRepository repository{0.5};
    NotificationRepository notificationRepository{"notifications.csv"};

    TenantService service{repository, notificationRepository};

    Console console{service};
    console.run();

    return 0;
}
