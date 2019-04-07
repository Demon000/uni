#include <string>
#include <vector>
#include <exception>

#include "TenantRepository.h"

using std::string;
using std::vector;
using std::exception;

void TenantRepository::addTenant(const Tenant& tenant) {
    tenants.push_back(tenant);
}

Tenant TenantRepository::getTenantByNumber(int number) {
    for (const auto& t: tenants) {
        if (t.getNumber() == number) {
            return t;
        }
    }

    throw exception();
}

vector<Tenant> TenantRepository::getTenants() {
    return tenants;
}

vector<Tenant> TenantRepository::getTenantsBySurface(int surface) {
    vector<Tenant> filtered;
    for (const auto& t: tenants) {
        if (t.getSurface() == surface) {
            filtered.push_back(t);
        }
    }

    return filtered;
}

vector<Tenant> TenantRepository::getTenantsByType(const string& type) {
    vector<Tenant> filtered;
    for (const auto& t: tenants) {
        if (t.getType() == type) {
            filtered.push_back(t);
        }
    }

    return filtered;
}

Tenant TenantRepository::updateTenant(Tenant& tenant, string name) {
    for (auto& t: tenants) {
        if (t == tenant) {
            t.setName(name);
            tenant.setName(name);
            return t;
        }
    }

    throw exception();
}

void TenantRepository::removeTenant(const Tenant& tenant) {
    for (auto it = tenants.begin(); it != tenants.end(); it++) {
        const Tenant& t = *it;
        if (t == tenant) {
            tenants.erase(it);
            return;
        }
    }

    throw exception();
}
