#include <algorithm>
#include <string>
#include <vector>

#include "TenantService.h"
using std::sort;
using std::string;
using std::vector;

TenantService::TenantService(TenantRepository* repository) :
    repository{repository} {}

Tenant* TenantService::createTenant(int number, const string& name,
        int surface, const string& type) const {
    Tenant* tenant = new Tenant(number, name, surface, type);
    repository->addTenant(tenant);
    return tenant;
}

Tenant* TenantService::getTenant(int number) const {
    return repository->getTenantByNumber(number);
}

vector<Tenant*> TenantService::getTenantsBySurface(int surface) const {
    return repository->getTenantsBySurface(surface);
}

vector<Tenant*> TenantService::getTenantsByType(const string& type) const {
    return repository->getTenantsByType(type);
}

vector<Tenant*> TenantService::getTenantsSortedBy(TenantSortType by) const {
    vector<Tenant*> tenants = repository->getTenants();
    sort(tenants.begin(), tenants.end(), [&](const Tenant* first,
            const Tenant* second) {
        if (by == TenantSortType::SortByName) {
            return first->getName() < second->getName();
        } else if (by == TenantSortType::SortByType) {
            return first->getType() < second->getType();
        } else if (by == TenantSortType::SortBySurface) {
            return first->getSurface() < second->getSurface();
        } else {
            return first->getType() < second->getType() ||
                    first->getSurface() < second->getSurface();
        }
    });

    return tenants;
}

Tenant* TenantService::updateTenant(int number, string name) const {
    Tenant* tenant = repository->getTenantByNumber(number);
    repository->updateTenant(tenant, name);
    return tenant;
}

void TenantService::removeTenant(int number) const {
    const Tenant* tenant = repository->getTenantByNumber(number);
    repository->removeTenant(tenant);
    delete tenant;
}

TenantService::~TenantService() {
    vector<Tenant*> tenants = repository->getTenants();
    for (const auto t: tenants) {
        delete t;
    }
}
