#include <vector>

#include "../entities/Tenant.h"

#ifndef TENANT_REPOSITORY_H
#define TENANT_REPOSITORY_H

class TenantRepository {
public:
	/**
	 * Add a tenant.
	 *
	 * @param tenant The tenant to be added.
	 */
    void addTenant(const Tenant&);

    /**
     * Get a tenant by the apartment number.
     *
     * @param The apartment number to look for.
     *
     * @return The tenant if found.
     */
    Tenant& getTenantByNumber(int);

    /**
     * Get all the tenants.
     *
     * @return The tenants.
     */
    std::vector<Tenant>& getTenants();

     /**
     * Get the tenants matching a surface.
     *
     * @param surface The surface to look for.
     *
     * @return The tenants matching the given surface.
     */
    std::vector<Tenant> getTenantsBySurface(int);

     /**
     * Get the tenants matching a type.
     *
     * @param type The type to look for.
     *
     * @return The tenants matching the given type.
     */
    std::vector<Tenant> getTenantsByType(const std::string&);

     /**
     * Update the name of a tenant.
     *
     * @param tenant The tenant to update.
     * @param name The new name of the tenant.
     */
    void updateTenant(Tenant&, std::string);

     /**
     * Remove a tenant.
     *
     * @param tenant The tenant to remove.
     */
    void removeTenant(const Tenant&);

private:
    std::vector<Tenant> tenants;
};

#endif // TENANT_REPOSITORY_H
