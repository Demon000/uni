#include <string>
#include <vector>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/ExceptionRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/TenantService.h"

#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
    Console(TenantService&);
    void run();

private:
    int readInt(const std::string&) const;
    std::string readStr(const std::string&) const;
    void printTenant(const Tenant&, const std::string&) const;
    void printTenants(std::vector<Tenant>, const std::string&) const;
    void addTenant();
    void updateTenant();
    void deleteTenant();
    void showTenants() const;
    void findApartment() const;
    void filterApartments() const;
    void sortApartments() const;
    void addNotifiedApartment() const;
    void showNotifiedTenats() const;
    void deleteNotifiedApartments() const;
    void generateNotifiedApartments() const;
    void undo();
    void showSurfaceReport() const;
    void goodbye() const;
    void addTenants();
    int askOption();

    TenantService& service;
};

#endif // CONSOLE_H
