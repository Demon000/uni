#include "../list/List.h"
#include "../entities/Tenant.h"

#ifndef TENANT_REPOSITORY_H
#define TENANT_REPOSITORY_H

class TenantRepository {
public:
    void addTenant(const Tenant&);
    Tenant getTenantByNumber(int);
    List<Tenant> getTenants();
    List<Tenant> getTenantsBySurface(int);
    List<Tenant> getTenantsByType(const std::string&);
    Tenant updateTenant(Tenant&, std::string);
    void removeTenant(const Tenant&);

private:
    List<Tenant> tenants;
};

#endif // TENANT_REPOSITORY_H
