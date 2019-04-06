#include <vector>

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
    TenantService(TenantRepository*);
    ~TenantService();

    Tenant* createTenant(int, const std::string&, int, const std::string&) const;
    Tenant* getTenant(int) const;
    std::vector<Tenant*> getTenantsBySurface(int) const;
    std::vector<Tenant*> getTenantsByType(const std::string&) const;
    std::vector<Tenant*> getTenantsSortedBy(TenantSortType) const;
    Tenant* updateTenant(int, std::string) const;
    void removeTenant(int) const;

private:
    TenantRepository* repository;
};

#endif // TENANT_SERVICE_H
