#include <algorithm>
#include <string>
#include <vector>
#include <exception>

#include "TenantService.h"

using std::sort;
using std::string;
using std::vector;
using std::exception;

TenantService::TenantService(TenantRepository& repository) :
    repository(repository) {}

Tenant TenantService::createTenant(int number, const string& name,
        int surface, const string& type) {
    try {
        repository.getTenantByNumber(number);
    } catch (exception&) {
        const Tenant tenant{number, name, surface, type};
        repository.addTenant(tenant);
        return tenant;
    }

    throw TenantExistsException();
}

Tenant& TenantService::getTenant(int number) const {
    return repository.getTenantByNumber(number);
}

vector<Tenant>& TenantService::getTenants() const {
    return repository.getTenants();
}

vector<Tenant> TenantService::getTenantsBySurface(int surface) const {
    return repository.getTenantsBySurface(surface);
}

vector<Tenant> TenantService::getTenantsByType(const string& type) const {
    return repository.getTenantsByType(type);
}

vector<Tenant> TenantService::getTenantsSortedBy(TenantSortType by) const {
    vector<Tenant> tenants = repository.getTenants();
    sort(tenants.begin(), tenants.end(), [&](const Tenant& first,
            const Tenant& second) {
        if (by == TenantSortType::SortByName) {
            return first.getName() < second.getName();
        } else if (by == TenantSortType::SortBySurface) {
            return first.getSurface() < second.getSurface();
        } else {
            return first.getType() < second.getType() ||
                    first.getSurface() < second.getSurface();
        }
    });

    return tenants;
}

Tenant& TenantService::updateTenant(int number, string name) {
    Tenant& tenant = repository.getTenantByNumber(number);
    repository.updateTenant(tenant, name);
    return tenant;
}

Tenant TenantService::removeTenant(int number) {
    Tenant tenant = repository.getTenantByNumber(number);
    repository.removeTenant(tenant);
    return tenant;
}
