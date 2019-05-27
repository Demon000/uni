#include "../observe/Observe.h"
#include "TenantService.h"

#include <functional>

#ifndef OBSERVABLE_TENANT_SERVICE_H
#define OBSERVABLE_TENANT_SERVICE_H

typedef std::function<void()> listenerType;

class ObservableTenantService : public TenantService, public Observable {
public:
    ObservableTenantService(BaseRepository& repository,
            NotificationRepository& notificationRepository)
            : TenantService(repository, notificationRepository) {
        //
    }

    Tenant createTenant(int number, const std::string& name,
            int surface, const std::string& type, bool skip=false) {
        Tenant tenant = TenantService::createTenant(number, name, surface, type, skip);
        notify(ObserveEvent::CHANGE);
        return tenant;
    }

    Tenant updateTenant(int number, std::string name, bool skip=false) {
        Tenant tenant = TenantService::updateTenant(number, name, skip);
        notify(ObserveEvent::CHANGE);
        return tenant;
    }

    Tenant removeTenant(int number, bool skip=false) {
        Tenant tenant = TenantService::removeTenant(number, skip);
        notify(ObserveEvent::CHANGE);
        return tenant;
    }

    void addNotification(int number) const {
        TenantService::addNotification(number);
        notify(ObserveEvent::CHANGE);
    }

    void addRandomNotifications(int length) const {
        TenantService::addRandomNotifications(length);
        notify(ObserveEvent::CHANGE);
    }

    void removeNotifications() const {
        TenantService::removeNotifications();
        notify(ObserveEvent::CHANGE);
    }

    void undo() {
        TenantService::undo();
        notify(ObserveEvent::CHANGE);
    }

private:
    std::vector<listenerType> listeners;
};

#endif // OBSERVABLE_TENANT_SERVICE_H
