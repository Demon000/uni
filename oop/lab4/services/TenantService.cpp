#include <string>
#include <exception>

#include "TenantService.h"

using std::string;
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

Tenant TenantService::getTenant(int number) const {
    return repository.getTenantByNumber(number);
}

List<Tenant> TenantService::getTenants() const {
    return repository.getTenants();
}

List<Tenant> TenantService::getTenantsBySurface(int surface) const {
    return repository.getTenantsBySurface(surface);
}

List<Tenant> TenantService::getTenantsByType(const string& type) const {
    return repository.getTenantsByType(type);
}

List<Tenant> TenantService::getTenantsSortedBy(TenantSortType by) const {
    List<Tenant> tenants = repository.getTenants();
    tenants.sort([&](const Tenant& first,
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

Tenant TenantService::updateTenant(int number, string name) {
    Tenant tenant = repository.getTenantByNumber(number);
    repository.updateTenant(tenant, name);
    return tenant;
}

Tenant TenantService::removeTenant(int number) {
    Tenant tenant = repository.getTenantByNumber(number);
    repository.removeTenant(tenant);
    return tenant;
}
