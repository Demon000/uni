#include <string>
#include <vector>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/TenantService.h"

#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
    Console(TenantService&);
    void run() const;

private:
    int readInt(const std::string&) const;
    std::string readStr(const std::string&) const;
    void printTenant(const Tenant&, const std::string&) const;
    void printTenants(std::vector<Tenant>, const std::string&) const;
    void addTenant() const;
    void updateTenant() const;
    void deleteTenant() const;
    void showTenants() const;
    void findApartment() const;
    void filterApartments() const;
    void sortApartments() const;
    void addNotifiedApartment() const;
    void showNotifiedTenats() const;
    void deleteNotifiedApartments() const;
    void generateNotifiedApartments() const;
    void goodbye() const;
    void addTenants() const;
    int askOption() const;

    TenantService& service;
};

#endif // CONSOLE_H
