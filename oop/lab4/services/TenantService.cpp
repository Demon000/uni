#include <algorithm>
#include <string>
#include <vector>
#include <exception>
#include <random>
#include <chrono>
#include <memory>

#include "TenantService.h"

using std::sort;
using std::string;
using std::vector;
using std::exception;
using std::chrono::system_clock;
using std::shuffle;
using std::default_random_engine;
using std::unique_ptr;
using std::move;
using std::unordered_map;
using std::to_string;

UndoAction::UndoAction(const Tenant& tenant) : tenant{tenant} {}
UndoCreateAction::UndoCreateAction(const Tenant& tenant) : UndoAction(tenant) {}
UndoUpdateAction::UndoUpdateAction(const Tenant& tenant) : UndoAction(tenant) {}
UndoDeleteAction::UndoDeleteAction(const Tenant& tenant) : UndoAction(tenant) {}

void UndoCreateAction::doUndo(TenantService& service) {
    service.removeTenant(tenant.getNumber(), true);
}

void UndoUpdateAction::doUndo(TenantService& service) {
    service.updateTenant(tenant.getNumber(), tenant.getName(), true);
}

void UndoDeleteAction::doUndo(TenantService& service) {
    service.createTenant(tenant.getNumber(), tenant.getName(),
            tenant.getSurface(), tenant.getType(), true);
}

TenantService::TenantService(BaseRepository& repository,
        NotificationRepository& notificationRepository) :
    repository(repository), notificationRepository(notificationRepository) {}

Tenant TenantService::createTenant(int number, const string& name,
        int surface, const string& type, bool skip) {
    try {
        repository.getTenantByNumber(number);
    } catch (TenantMissingException&) {
        const Tenant tenant{number, name, surface, type};
        if (!skip) {
            unique_ptr<UndoAction> action(new UndoCreateAction{tenant});
            undoActions.push_back(move(action));
        }

        repository.addTenant(tenant);

        return tenant;
    }

    throw TenantExistsException();
}

Tenant TenantService::getTenant(int number) const {
    return repository.getTenantByNumber(number);
}

vector<Tenant> TenantService::getTenants() const {
    return repository.getTenants();
}

vector<Tenant> TenantService::getFilteredTenants(const string& text) const {
    vector<Tenant> tenants = repository.getTenants();
    vector<Tenant> filtered;

    for (const Tenant& tenant : tenants) {
        string number = to_string(tenant.getNumber());
        if (number.find(text) != string::npos) {
            filtered.push_back(tenant);
            continue;
        }

        string name = tenant.getName();
        if (name.find(text) != string::npos) {
            filtered.push_back(tenant);
            continue;
        }

        string surface = to_string(tenant.getSurface());
        if (surface.find(text) != string::npos) {
            filtered.push_back(tenant);
            continue;
        }

        string type = tenant.getType();
        if (type.find(text) != string::npos) {
            filtered.push_back(tenant);
            continue;
        }
    }

    return filtered;
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

unordered_map<int, int> TenantService::getSurfaceReport() const {
    unordered_map<int, int> surfaceReport;

    vector<Tenant> tenants = repository.getTenants();
    for (const Tenant& tenant : tenants) {
        int surface = tenant.getSurface();
        surfaceReport[surface]++;
    }

    return surfaceReport;
}

Tenant TenantService::updateTenant(int number, string name, bool skip) {
    Tenant tenant = repository.getTenantByNumber(number);
    if (!skip) {
        unique_ptr<UndoAction> action{new UndoUpdateAction{tenant}};
        undoActions.push_back(move(action));
    }

    repository.updateTenant(tenant, name);

    return tenant;
}

Tenant TenantService::removeTenant(int number, bool skip) {
    Tenant tenant = repository.getTenantByNumber(number);
    if (!skip) {
        unique_ptr<UndoAction> action{new UndoDeleteAction{tenant}};
        undoActions.push_back(move(action));
    }

    repository.removeTenant(tenant);

    try {
        notificationRepository.removeNumber(number);
    } catch (exception&) {
        // ignore
    }

    return tenant;
}

void TenantService::addNotification(int number) const {
    repository.getTenantByNumber(number);

    try {
        notificationRepository.numberExists(number);
    } catch (exception&) {
        notificationRepository.addNumber(number);
        return;
    }

    throw NumberExistsException();
}

void TenantService::addRandomNotifications(int length) const {
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

vector<Tenant> TenantService::getTenantsToNotify() const {
    vector<int> numbers = notificationRepository.getNumbers();
    vector<Tenant> tenants;

    for (const int& number : numbers) {
        Tenant tenant = repository.getTenantByNumber(number);
        tenants.push_back(tenant);
    }

    return tenants;
}

int TenantService::getNumberOfNotifications() const {
    vector<int> numbers = notificationRepository.getNumbers();
    return numbers.size();
}

void TenantService::removeNotifications() const {
    notificationRepository.removeNumbers();
}

void TenantService::undo() {
    if (!undoActions.size()) {
        throw NoUndoActions();
    }

    unique_ptr<UndoAction> action = move(undoActions.back());
    undoActions.pop_back();

    action->doUndo(*this);
}
