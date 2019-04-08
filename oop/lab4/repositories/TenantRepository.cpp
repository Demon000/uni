#include <string>
#include <exception>

#include "TenantRepository.h"

using std::string;
using std::exception;

void TenantRepository::addTenant(const Tenant& tenant) {
    tenants.push_back(tenant);
}

Tenant TenantRepository::getTenantByNumber(int number) {
    Tenant tenant;
    int done = tenants.for_each([&](const Tenant& t) {
        if (t.getNumber() == number) {
            tenant = t;
            return true;
        }

        return false;
    });

    if (done) {
        return tenant;
    }

    throw exception();
}

List<Tenant> TenantRepository::getTenants() {
    List<Tenant> all;
    tenants.for_each([&](const Tenant& t) {
        all.push_back(t);
        return false;
    });

    return all;
}

List<Tenant> TenantRepository::getTenantsBySurface(int surface) {
    List<Tenant> filtered;
    tenants.for_each([&](const Tenant& t) {
        if (t.getSurface() == surface) {
            filtered.push_back(t);
        }

        return false;
    });

    return filtered;
}

List<Tenant> TenantRepository::getTenantsByType(const string& type) {
    List<Tenant> filtered;
    tenants.for_each([&](const Tenant& t) {
        if (t.getType() == type) {
            filtered.push_back(t);
        }

        return false;
    });

    return filtered;
}

Tenant TenantRepository::updateTenant(Tenant& tenant, string name) {
    bool done = tenants.for_each([&](Tenant& t) {
        if (t == tenant) {
            t.setName(name);
            tenant.setName(name);
            return true;
        }

        return false;
    });


    if (done) {
        return tenant;
    }

    throw exception();
}

void TenantRepository::removeTenant(const Tenant& tenant) {
    int i = 0;
    bool done = tenants.for_each([&](const Tenant& t) {
        if (t == tenant) {
            tenants.remove(i);
            return true;
        }

        i++;

        return false;
    });

    if (done) {
        return;
    }

    throw exception();
}
