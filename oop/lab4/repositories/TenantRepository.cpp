#include <string>
#include <vector>
#include <exception>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "TenantRepository.h"

using std::string;
using std::vector;
using std::exception;
using std::copy_if;
using std::back_inserter;
using std::ifstream;
using std::ofstream;
using std::stringstream;

TenantRepository::TenantRepository(const string& path) : path(path) {
    readTenants();
}

vector<Tenant> TenantRepository::readTenants() const {
    vector<Tenant> tenants;
    ifstream in(path);

    int number;
    string name;
    int surface;
    string type;

    if (!in) {
        writeTenants(tenants);
    }

    string part;

    while (getline(in, part, ',')) {
        number = stoi(part);

        getline(in, part, ',');
        name = part;

        getline(in, part, ',');
        surface = stoi(part);

        getline(in, part);
        type = part;

        Tenant tenant{number, name, surface, type};
        tenants.push_back(tenant);
    }

    return tenants;
}

void TenantRepository::writeTenants(const vector<Tenant>& tenants) const {
    ofstream out(path);

    for (const Tenant& tenant : tenants) {
        out << tenant.getNumber() << ","
            << tenant.getName() << ","
            << tenant.getSurface() << ","
            << tenant.getType() << "\n";
    }
}

void TenantRepository::addTenant(const Tenant& tenant) const {
    vector<Tenant> tenants = readTenants();
    tenants.push_back(tenant);
    writeTenants(tenants);
}

Tenant TenantRepository::getTenantByNumber(int number) const {
    vector<Tenant> tenants = readTenants();
    auto it = find_if(tenants.begin(), tenants.end(), [&](const Tenant& t) {
        return t.getNumber() == number;
    });

    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    return *it;
}

vector<Tenant> TenantRepository::getTenants() const {
    vector<Tenant> tenants = readTenants();
    return tenants;
}

vector<Tenant> TenantRepository::getTenantsBySurface(int surface) const {
    vector<Tenant> tenants = readTenants();
    vector<Tenant> filtered;
    copy_if(tenants.begin(), tenants.end(), back_inserter(filtered), [&](const Tenant& t) {
        return t.getSurface() == surface;
    });

    return filtered;
}

vector<Tenant> TenantRepository::getTenantsByType(const string& type) const {
    vector<Tenant> tenants = readTenants();
    vector<Tenant> filtered;
    copy_if(tenants.begin(), tenants.end(), back_inserter(filtered), [&](const Tenant& t) {
        return t.getType() == type;
    });

    return filtered;
}

void TenantRepository::updateTenant(Tenant& tenant, const string& name) const {
    vector<Tenant> tenants = readTenants();
    auto it = find(tenants.begin(), tenants.end(), tenant);
    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    it->setName(name);
    tenant.setName(name);
    writeTenants(tenants);
}

void TenantRepository::removeTenant(const Tenant& tenant) const {
    vector<Tenant> tenants = readTenants();
    auto it = find(tenants.begin(), tenants.end(), tenant);
    if (it == tenants.end()) {
        throw TenantMissingException();
    }

    tenants.erase(it);
    writeTenants(tenants);
}
