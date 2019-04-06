#include <vector>

#include "../entities/Tenant.h"

#ifndef TENANT_REPOSITORY_H
#define TENANT_REPOSITORY_H

class TenantRepository {
public:
    void addTenant(const Tenant&);
    Tenant getTenantByNumber(int);
    std::vector<Tenant> getTenants();
    std::vector<Tenant> getTenantsBySurface(int);
    std::vector<Tenant> getTenantsByType(const std::string&);
    Tenant updateTenant(Tenant&, std::string);
    void removeTenant(const Tenant&);

private:
    std::vector<Tenant> tenants;
};

#endif // TENANT_REPOSITORY_H
