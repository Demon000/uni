#include <exception>
#include <algorithm>
#include <random>
#include <chrono>

#include "NotificationService.h"

using std::exception;
using std::vector;
using std::chrono::system_clock;
using std::shuffle;
using std::default_random_engine;

NotificationService::NotificationService(NotificationRepository& notificationRepository,
        TenantRepository& tenantRepository) : notificationRepository(notificationRepository),
        tenantRepository(tenantRepository) {}

void NotificationService::addNotification(int number) {
    tenantRepository.getTenantByNumber(number);

    try {
        notificationRepository.getTenantByNumber(number);
    } catch (exception&) {
        notificationRepository.addNumber(number);
        return;
    }

    throw new NumberExistsException();
}

void NotificationService::addRandomNotifications(int length) {
    removeNotifications();

    vector<Tenant> tenants = tenantRepository.getTenants();
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

vector<Tenant> NotificationService::getTenantsToNotify() {
    vector<int> numbers = notificationRepository.getNumbers();
    vector<int> numbersToRemove;
    vector<Tenant> tenants;

    for (const int& number : numbers) {
        try {
            Tenant tenant = tenantRepository.getTenantByNumber(number);
            tenants.push_back(tenant);
        } catch (exception&) {
            // ignore
        }
    }

    return tenants;
}

void NotificationService::removeNotifications() {
    notificationRepository.removeNumbers();
}
