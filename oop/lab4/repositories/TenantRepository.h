#include <vector>

#include "../entities/Tenant.h"

#ifndef TENANT_REPOSITORY_H
#define TENANT_REPOSITORY_H

class TenantRepository {
public:
    void addTenant(Tenant*);
    Tenant* getTenantByNumber(int) const;
    std::vector<Tenant*> getTenants() const;
    std::vector<Tenant*> getTenantsBySurface(int) const;
    std::vector<Tenant*> getTenantsByType(const std::string&) const;
    void updateTenant(Tenant*, std::string) const;
    void removeTenant(const Tenant*);

private:
    std::vector<Tenant*> tenants;
};

#endif // TENANT_REPOSITORY_H
