#include "repositories/TenantRepository.h"
#include "services/TenantService.h"
#include "ui/Console.h"

int main() {
    TenantRepository repository;
    TenantService service{repository};
    Console console{service};

    return 0;
}
