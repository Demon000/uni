#include "TenantService.h"

#include <functional>

#ifndef OBSERVABLE_TENANT_SERVICE_H
#define OBSERVABLE_TENANT_SERVICE_H

typedef std::function<void()> listenerType;

class ObservableTenantService : public TenantService {
public:
    ObservableTenantService(BaseRepository& repository,
            NotificationRepository& notificationRepository)
            : TenantService(repository, notificationRepository) {
        //
    }

    Tenant createTenant(int number, const std::string& name,
            int surface, const std::string& type, bool skip=false) {
        Tenant tenant = TenantService::createTenant(number, name, surface, type, skip);
        emitChanged();
        return tenant;
    }

    Tenant updateTenant(int number, std::string name, bool skip=false) {
        Tenant tenant = TenantService::updateTenant(number, name, skip);
        emitChanged();
        return tenant;
    }

    Tenant removeTenant(int number, bool skip=false) {
        Tenant tenant = TenantService::removeTenant(number, skip);
        emitChanged();
        return tenant;
    }

    void addNotification(int number) const {
        TenantService::addNotification(number);
        emitChanged();
    }

    void addRandomNotifications(int length) const {
        TenantService::addRandomNotifications(length);
        emitChanged();
    }

    void removeNotifications() const {
        TenantService::removeNotifications();
        emitChanged();
    }

    void undo() {
        TenantService::undo();
        emitChanged();
    }

    void emitChanged() const {
        for (const listenerType& listener : listeners) {
            listener();
        }
    }

    void onChanged(const listenerType& listener) {
        listeners.push_back(listener);
    }

private:
    std::vector<listenerType> listeners;
};

#endif // OBSERVABLE_TENANT_SERVICE_H
