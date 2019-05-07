#include <vector>
#include <string>

#include "../entities/Tenant.h"
#include "../repositories/BaseRepository.h"

#ifndef TENANT_REPOSITORY_H
#define TENANT_REPOSITORY_H

class TenantRepository : public BaseRepository {
public:
    TenantRepository(const std::string&);

    /**
     * Add a tenant.
     *
     * @param tenant The tenant to be added.
     */
    void addTenant(const Tenant&) override;

    /**
     * Get a tenant by the apartment number.
     *
     * @param The apartment number to look for.
     *
     * @return The tenant if found.
     */
    Tenant getTenantByNumber(int) override;

    /**
     * Get all the tenants.
     *
     * @return The tenants.
     */
    std::vector<Tenant> getTenants() override;

     /**
     * Get the tenants matching a surface.
     *
     * @param surface The surface to look for.
     *
     * @return The tenants matching the given surface.
     */
    std::vector<Tenant> getTenantsBySurface(int) override;

     /**
     * Get the tenants matching a type.
     *
     * @param type The type to look for.
     *
     * @return The tenants matching the given type.
     */
    std::vector<Tenant> getTenantsByType(const std::string&) override;

     /**
     * Update the name of a tenant.
     *
     * @param tenant The tenant to update.
     * @param name The new name of the tenant.
     */
    void updateTenant(Tenant&, const std::string&) override;

     /**
     * Remove a tenant.
     *
     * @param tenant The tenant to remove.
     */
    void removeTenant(const Tenant&) override;

private:
    /**
     * Read the numbers from the storage file.
     *
     * @return The numbers read.
     */
    void readTenants();

    /**
     * Write numbers to the storage file.
     *
     * @param numbers The numbers to write.
     */
    void writeTenants() const;

    std::string path;
};

#endif // TENANT_REPOSITORY_H
