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

TenantRepository::TenantRepository(const string& path) : path(path) {}

vector<Tenant> TenantRepository::readTenants() {
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

void TenantRepository::addTenant(const Tenant& tenant) {
    tenants = readTenants();
    BaseRepository::addTenant(tenant);
    writeTenants(tenants);
}

Tenant TenantRepository::getTenantByNumber(int number) {
    tenants = readTenants();
    return BaseRepository::getTenantByNumber(number);
}

vector<Tenant> TenantRepository::getTenants() {
    tenants = readTenants();
    return BaseRepository::getTenants();
}

vector<Tenant> TenantRepository::getTenantsBySurface(int surface) {
    tenants = readTenants();
    return BaseRepository::getTenantsBySurface(surface);
}

vector<Tenant> TenantRepository::getTenantsByType(const string& type) {
    tenants = readTenants();
    return BaseRepository::getTenantsByType(type);
}

void TenantRepository::updateTenant(Tenant& tenant, const string& name) {
    tenants = readTenants();
    BaseRepository::updateTenant(tenant, name);
    writeTenants(tenants);
}

void TenantRepository::removeTenant(const Tenant& tenant) {
    tenants = readTenants();
    BaseRepository::removeTenant(tenant);
    writeTenants(tenants);
}
