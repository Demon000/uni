#include <string>
#include <vector>
#include <exception>

#include "TenantRepository.h"

using std::string;
using std::vector;
using std::exception;

void TenantRepository::addTenant(Tenant* tenant) {
    tenants.push_back(tenant);
}

Tenant* TenantRepository::getTenantByNumber(int number) const {
    for (auto t: tenants) {
        if (t->getNumber() == number) {
            return t;
        }
    }

    throw exception();
}

vector<Tenant*> TenantRepository::getTenants() const {
    return tenants;
}

vector<Tenant*> TenantRepository::getTenantsBySurface(int surface) const {
    vector<Tenant*> filtered;
    for (auto t: tenants) {
        if (t->getSurface() == surface) {
            filtered.push_back(t);
        }
    }

    return filtered;
}

vector<Tenant*> TenantRepository::getTenantsByType(const string& type) const {
    vector<Tenant*> filtered;
    for (auto t: tenants) {
        if (t->getType() == type) {
            filtered.push_back(t);
        }
    }

    return filtered;
}

void TenantRepository::updateTenant(Tenant* tenant, string name) const {
    tenant->setName(name);
}

void TenantRepository::removeTenant(const Tenant* tenant) {
    for (auto it = tenants.begin(); it != tenants.end(); it++) {
        Tenant* t = *it;
        if (t == tenant) {
            tenants.erase(it);
            return;
        }
    }
}
