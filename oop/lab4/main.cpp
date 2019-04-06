#include <iostream>

#include "entities/Tenant.h"
#include "repositories/TenantRepository.h"
#include "services/TenantService.h"

using std::endl;

int main() {
    TenantRepository* repository = new TenantRepository();
    TenantService* service = new TenantService(repository);

    return 0;
}
