#include <string>
#include <vector>
#include <exception>
#include <algorithm>

#include "TenantRepository.h"

using std::string;
using std::vector;
using std::exception;
using std::copy_if;
using std::back_inserter;

void TenantRepository::addTenant(const Tenant& tenant) {
    tenants.push_back(tenant);
}

Tenant& TenantRepository::getTenantByNumber(int number) {
    auto it = find_if(tenants.begin(), tenants.end(), [&](const Tenant& t) {
        return t.getNumber() == number;
    });

    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    return *it;
}

vector<Tenant>& TenantRepository::getTenants() {
    return tenants;
}

vector<Tenant> TenantRepository::getTenantsBySurface(int surface) {
    vector<Tenant> filtered;
    copy_if(tenants.begin(), tenants.end(), back_inserter(filtered), [&](const Tenant& t) {
        return t.getSurface() == surface;
    });

    return filtered;
}

vector<Tenant> TenantRepository::getTenantsByType(const string& type) {
    vector<Tenant> filtered;
    copy_if(tenants.begin(), tenants.end(), back_inserter(filtered), [&](const Tenant& t) {
        return t.getType() == type;
    });

    return filtered;
}

void TenantRepository::updateTenant(Tenant& tenant, string name) {
    auto it = find(tenants.begin(), tenants.end(), tenant);
    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    it->setName(name);
    tenant.setName(name);
}

void TenantRepository::removeTenant(const Tenant& tenant) {
    auto it = find(tenants.begin(), tenants.end(), tenant);
    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    tenants.erase(it);
}
