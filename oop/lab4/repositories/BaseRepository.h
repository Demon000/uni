#include <vector>
#include <string>

#include "../entities/Tenant.h"

#ifndef BASE_REPOSITORY_H
#define BASE_REPOSITORY_H

class BaseRepository {
public:
    /**
     * Add a tenant.
     *
     * @param tenant The tenant to be added.
     */
    virtual void addTenant(const Tenant&);

    /**
     * Get a tenant by the apartment number.
     *
     * @param The apartment number to look for.
     *
     * @return The tenant if found.
     */
    virtual Tenant getTenantByNumber(int);

    /**
     * Get all the tenants.
     *
     * @return The tenants.
     */
    virtual std::vector<Tenant> getTenants();

     /**
     * Get the tenants matching a surface.
     *
     * @param surface The surface to look for.
     *
     * @return The tenants matching the given surface.
     */
    virtual std::vector<Tenant> getTenantsBySurface(int);

     /**
     * Get the tenants matching a type.
     *
     * @param type The type to look for.
     *
     * @return The tenants matching the given type.
     */
    virtual std::vector<Tenant> getTenantsByType(const std::string&);

     /**
     * Update the name of a tenant.
     *
     * @param tenant The tenant to update.
     * @param name The new name of the tenant.
     */
    virtual void updateTenant(Tenant&, const std::string&);

     /**
     * Remove a tenant.
     *
     * @param tenant The tenant to remove.
     */
    virtual void removeTenant(const Tenant&);

protected:
    std::vector<Tenant> tenants;
};

#endif // BASE_REPOSITORY_H
