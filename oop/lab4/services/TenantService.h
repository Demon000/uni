#include <vector>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"

#ifndef TENANT_SERVICE_H
#define TENANT_SERVICE_H

enum TenantSortType {
    SortByName,
    SortBySurface,
    SortByTypeAndSurface,
};

class TenantService {
public:
    /**
     * Create a service.
     *
     * @param repository The repository to use in the service.
     */
    TenantService(TenantRepository&);

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
    Tenant createTenant(int, const std::string&, int, const std::string&);

    /**
     * Get a tenant.
     *
     * @param number The apartment number to look for.
     *
     * @return The tenant, if found.
     */
    Tenant& getTenant(int) const;

    /**
     * Get all the tenants.
     *
     * @return The tenants.
     */
    std::vector<Tenant>& getTenants() const;

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
     * Update a tenant.
     *
     * @param number The apartment number.
     * @param name The new name of the tenant.
     *
     * @return The updated tenant.
     */
    Tenant& updateTenant(int, std::string);

     /**
     * Remove a tenant.
     *
     * @param number The apartment number.
     *
     * @return The removed tenar.
     */
    Tenant removeTenant(int);

private:
    TenantRepository& repository;
};

#endif // TENANT_SERVICE_H
