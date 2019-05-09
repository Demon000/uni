#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "BaseRepository.h"

using std::string;
using std::vector;
using std::exception;
using std::copy_if;
using std::find_if;
using std::back_inserter;
using std::ifstream;
using std::ofstream;
using std::stringstream;

void BaseRepository::addTenant(const Tenant& tenant) {
    tenants.push_back(tenant);
}

Tenant BaseRepository::getTenantByNumber(int number) {
    auto it = find_if(tenants.begin(), tenants.end(), [&](const Tenant& t) {
        return t.getNumber() == number;
    });

    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    return *it;
}

vector<Tenant> BaseRepository::getTenants() {
    return tenants;
}

vector<Tenant> BaseRepository::getTenantsBySurface(int surface) {
    vector<Tenant> filtered;
    copy_if(tenants.begin(), tenants.end(), back_inserter(filtered), [&](const Tenant& t) {
        return t.getSurface() == surface;
    });

    return filtered;
}

vector<Tenant> BaseRepository::getTenantsByType(const string& type) {
    vector<Tenant> filtered;
    copy_if(tenants.begin(), tenants.end(), back_inserter(filtered), [&](const Tenant& t) {
        return t.getType() == type;
    });

    return filtered;
}

void BaseRepository::updateTenant(Tenant& tenant, const string& name) {
    auto it = find(tenants.begin(), tenants.end(), tenant);
    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    it->setName(name);
    tenant.setName(name);
}

void BaseRepository::removeTenant(const Tenant& tenant) {
    auto it = find(tenants.begin(), tenants.end(), tenant);
    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    tenants.erase(it);
}
