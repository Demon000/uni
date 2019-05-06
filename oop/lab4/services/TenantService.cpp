#include <algorithm>
#include <string>
#include <vector>
#include <exception>
#include <random>
#include <chrono>

#include "TenantService.h"

using std::sort;
using std::string;
using std::vector;
using std::exception;
using std::chrono::system_clock;
using std::shuffle;
using std::default_random_engine;

TenantService::TenantService(TenantRepository& repository,
        NotificationRepository& notificationRepository) :
    repository(repository), notificationRepository(notificationRepository) {}

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

    try {
        notificationRepository.removeNumber(number);
    } catch (exception&) {
        // ignore
    }

    return tenant;
}

void TenantService::addNotification(int number) {
    repository.getTenantByNumber(number);

    try {
        notificationRepository.getTenantByNumber(number);
    } catch (exception&) {
        notificationRepository.addNumber(number);
        return;
    }

    throw new NumberExistsException();
}

void TenantService::addRandomNotifications(int length) {
    removeNotifications();

    vector<Tenant> tenants = repository.getTenants();
    auto seed = system_clock::now().time_since_epoch().count();
    shuffle(tenants.begin(), tenants.end(), default_random_engine(seed));

    for (const Tenant& tenant : tenants) {
        if (length <= 0) {
            break;
        }

        notificationRepository.addNumber(tenant.getNumber());
        length--;
    }
}

vector<Tenant> TenantService::getTenantsToNotify() {
    vector<int> numbers = notificationRepository.getNumbers();
    vector<Tenant> tenants;

    for (const int& number : numbers) {
        Tenant tenant = repository.getTenantByNumber(number);
        tenants.push_back(tenant);
    }

    return tenants;
}

void TenantService::removeNotifications() {
    notificationRepository.removeNumbers();
}
