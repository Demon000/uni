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

void TenantRepository::readTenants() {
    tenants.clear();

    ifstream in(path);

    int number;
    string name;
    int surface;
    string type;

    vector<string> words;
    string word, line;

   while(getline(in, line)) {
        std::stringstream ss(line);
        while(getline(ss, word, ',')) {
             words.push_back(word);
        }
   }

    for (auto it = words.begin(); it < words.end(); it += 4) {
        number = stoi(it[0]);
        name = it[1];
        surface = stoi(it[2]);
        type = it[3];

        Tenant tenant{number, name, surface, type};
        tenants.push_back(tenant);
    }
}

void TenantRepository::writeTenants() const {
    ofstream out(path);

    for (const Tenant& tenant : tenants) {
        out << tenant.getNumber() << ","
            << tenant.getName() << ","
            << tenant.getSurface() << ","
            << tenant.getType() << "\n";
    }
}

void TenantRepository::addTenant(const Tenant& tenant) {
    readTenants();
    BaseRepository::addTenant(tenant);
    writeTenants();
}

Tenant TenantRepository::getTenantByNumber(int number) {
    readTenants();
    return BaseRepository::getTenantByNumber(number);
}

vector<Tenant> TenantRepository::getTenants() {
    readTenants();
    return BaseRepository::getTenants();
}

vector<Tenant> TenantRepository::getTenantsBySurface(int surface) {
    readTenants();
    return BaseRepository::getTenantsBySurface(surface);
}

vector<Tenant> TenantRepository::getTenantsByType(const string& type) {
    readTenants();
    return BaseRepository::getTenantsByType(type);
}

void TenantRepository::updateTenant(Tenant& tenant, const string& name) {
    readTenants();
    BaseRepository::updateTenant(tenant, name);
    writeTenants();
}

void TenantRepository::removeTenant(const Tenant& tenant) {
    readTenants();
    BaseRepository::removeTenant(tenant);
    writeTenants();
}
