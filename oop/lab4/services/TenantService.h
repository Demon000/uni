#include "../list/List.h"
#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"

#ifndef TENANT_SERVICE_H
#define TENANT_SERVICE_H

enum TenantSortType {
    SortByName,
    SortBySurface,
    SortByType,
    SortByTypeAndSurface,
};

class TenantService {
public:
    TenantService(TenantRepository&);

    Tenant createTenant(int, const std::string&, int, const std::string&);
    Tenant getTenant(int) const;
    List<Tenant> getTenantsBySurface(int) const;
    List<Tenant> getTenantsByType(const std::string&) const;
    List<Tenant> getTenantsSortedBy(TenantSortType) const;
    Tenant updateTenant(int, std::string);
    void removeTenant(int);

private:
    TenantRepository& repository;
};

#endif // TENANT_SERVICE_H
