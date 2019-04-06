#include <iostream>

#include "entities/Tenant.h"
#include "repositories/TenantRepository.h"
#include "services/TenantService.h"

using std::endl;

int main() {
    TenantRepository repository;
    TenantService service{repository};

    return 0;
}
