#include <vector>

#include "../entities/Tenant.h"
#include "../repositories/NotificationRepository.h"
#include "../repositories/TenantRepository.h"

#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

class NotificationService {
public:
    /**
     * Create a notification service.
     *
     * @param notificationRepository The repository to use for notifications in the service.
     * @param tenantRepository The repository to use for tenants in the service.
     */
    NotificationService(NotificationRepository&, TenantRepository&);

    /**
     * Add an apartment number to the notification list.
     *
     * @param number The number of the apartment.
     */
    void addNotification(int);

    /**
     * Add multiple number of apartments to the notification list.
     *
     * @param number The number of apartments to be added.
     */
    void addRandomNotifications(int);

    /**
     * Get all the tenants that need to be notified.
     *
     * @param tenants The tenants.
     *
     * @return The tenants that need to be notified.
     */
    std::vector<Tenant> getTenantsToNotify();

    /**
     * Remove all the tenants that need to be notified.
     */
    void removeNotifications();

private:
    NotificationRepository& notificationRepository;
    TenantRepository& tenantRepository;
};

#endif // NOTIFICATION_SERVICE_H
