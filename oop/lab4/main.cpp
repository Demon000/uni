#include "repositories/TenantRepository.h"
#include "services/TenantService.h"
#include "ui/Console.h"

int main() {
    TenantRepository repository;
    NotificationRepository notificationRepository;

    TenantService service{repository};
    NotificationService notificationService{notificationRepository, repository};

    Console console{service, notificationService};
    console.run();

    return 0;
}
