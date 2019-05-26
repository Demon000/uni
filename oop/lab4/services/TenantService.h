#include <vector>
#include <string>
#include <memory>
#include <exception>
#include <unordered_map>

#include "../entities/Tenant.h"
#include "../repositories/BaseRepository.h"
#include "../repositories/NotificationRepository.h"

#ifndef TENANT_SERVICE_H
#define TENANT_SERVICE_H

enum TenantSortType {
    SortByName,
    SortBySurface,
    SortByTypeAndSurface,
};

class TenantService;

class NoUndoActions : public std::exception {};

class UndoAction {
public:
    UndoAction(const Tenant&);
    virtual void doUndo(TenantService&) = 0;

protected:
    Tenant tenant;
};

class UndoCreateAction : public UndoAction {
public:
    UndoCreateAction(const Tenant&);
    void doUndo(TenantService&) override;
};

class UndoUpdateAction : public UndoAction {
public:
    UndoUpdateAction(const Tenant&);
    void doUndo(TenantService&) override;
};

class UndoDeleteAction : public UndoAction {
public:
    UndoDeleteAction(const Tenant&);
    void doUndo(TenantService&) override;
};

class TenantService {
public:
    /**
     * Create a service.
     *
     * @param repository The repository to use in the service.
     * @param notificationRepository The repository to use for notifications in the service.
     */
    TenantService(BaseRepository&, NotificationRepository&);

    /**
     * Create a tenant.
     *
     * @param number The number of the apartment.
     * @param name The name of the tenant.
     * @param surface The surface of the apartment.
     * @param type The type of the apartment.
     *
     * @return The created tenant.
     */
    Tenant createTenant(int, const std::string&, int, const std::string&, bool skip=false);

    /**
     * Get a tenant.
     *
     * @param number The apartment number to look for.
     *
     * @return The tenant, if found.
     */
    Tenant getTenant(int) const;

    /**
     * Get all the tenants.
     *
     * @return The tenants.
     */
    std::vector<Tenant> getTenants() const;

    /**
     * Get tenants matching the a string.
     *
     * @return The matching tenants.
     */
    std::vector<Tenant> getFilteredTenants(const std::string&) const;

     /**
     * Get the tenants matching a surface.
     *
     * @param surface The surface to look for.
     *
     * @return The tenants matching the given surface.
     */
    std::vector<Tenant> getTenantsBySurface(int) const;

     /**
     * Get the tenants matching a type.
     *
     * @param type The type to look for.
     *
     * @return The tenants matching the given type.
     */
    std::vector<Tenant> getTenantsByType(const std::string&) const;

     /**
     * Get the tenants sorted by a criteria.
     *
     * @param type The type of the criteria.
     *
     * @return The sorted tenants.
     */
    std::vector<Tenant> getTenantsSortedBy(TenantSortType) const;

     /**
     * Get surface report of the apartments.
     *
     * @return The surface report.
     */
    std::unordered_map<int, int> getSurfaceReport() const;

     /**
     * Update a tenant.
     *
     * @param number The apartment number.
     * @param name The new name of the tenant.
     *
     * @return The updated tenant.
     */
    Tenant updateTenant(int, std::string, bool skip=false);

     /**
     * Remove a tenant.
     *
     * @param number The apartment number.
     *
     * @return The removed tenar.
     */
    Tenant removeTenant(int, bool skip=false);

    /**
     * Add an apartment number to the notification list.
     *
     * @param number The number of the apartment.
     */
    void addNotification(int) const;

    /**
     * Add multiple number of apartments to the notification list.
     *
     * @param number The number of apartments to be added.
     */
    void addRandomNotifications(int) const;

    /**
     * Get all the tenants that need to be notified.
     *
     * @param tenants The tenants.
     *
     * @return The tenants that need to be notified.
     */
    std::vector<Tenant> getTenantsToNotify() const;

    /**
     * Get number of apartments in the notification list.
     *
     * @return The number of notifications.
     */
    int getNumberOfNotifications() const;

    /**
     * Remove all the tenants that need to be notified.
     */
    void removeNotifications() const;

    /**
     * Undo the last action.
     */
    void undo();

private:
    std::vector<std::unique_ptr<UndoAction>> undoActions;
    BaseRepository& repository;
    NotificationRepository& notificationRepository;
};

#endif // TENANT_SERVICE_H
