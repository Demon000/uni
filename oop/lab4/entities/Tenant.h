#include <string>

#ifndef TENANT_H
#define TENANT_H

class Tenant {
public:
    /**
     * Create an empty tenant.
     */
    Tenant();

    /**
     * Create a tenant.
     *
     * @param number The number of the apartment.
     * @param name The name of the tenant.
     * @param surface The surface of the apartment.
     * @param type The type of the apartment.
     */
    Tenant(int, std::string, int, std::string);

    bool operator==(const Tenant&) const;

    /**
     * Get an user-friendly representation of the stored data.
     *
     * @return A string containing the representation.
     */
    std::string toString() const;

    /**
     * Get the apartament number of the tenant.
     *
     * @return The apartament number.
     */
    int getNumber() const;

    /**
     * Get the name of the tenant.
     *
     * @return The name of the tenant.
     */
    const std::string& getName() const;

    /**
     * Get the apartament surface of the tenant.
     *
     * @return The apartament surface.
     */
    int getSurface() const;

    /**
     * Get the apartament type of the tenant.
     *
     * @return The apartament type.
     */
    const std::string& getType() const;

    /**
     * Set the name of the tenant.
     *
     * @param name The new name of the tenant.
     */
    void setName(std::string);

private:
    int number;
    std::string name;
    int surface;
    std::string type;
};

class TenantMissingException : public std::exception {};
class TenantExistsException : public std::exception {};

#endif // TENANT_H
