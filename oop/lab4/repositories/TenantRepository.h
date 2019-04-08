#include "../list/List.h"
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
    Tenant getTenantByNumber(int);

    /**
     * Get all the tenants.
     *
     * @return The tenants.
     */
    List<Tenant> getTenants();

     /**
     * Get the tenants matching a surface.
     *
     * @param surface The surface to look for.
     *
     * @return The tenants matching the given surface.
     */
    List<Tenant> getTenantsBySurface(int);

     /**
     * Get the tenants matching a type.
     *
     * @param type The type to look for.
     *
     * @return The tenants matching the given type.
     */
    List<Tenant> getTenantsByType(const std::string&);

     /**
     * Update the name of a tenant.
     *
     * @param tenant The tenant to update.
     * @param name The new name of the tenant.
     *
     * @return The updated tenant.
     */
    Tenant updateTenant(Tenant&, std::string);

     /**
     * Remove a tenant.
     *
     * @param tenant The tenant to remove.
     */
    void removeTenant(const Tenant&);

private:
    List<Tenant> tenants;
};

#endif // TENANT_REPOSITORY_H
