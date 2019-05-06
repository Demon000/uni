#include <string>
#include <vector>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../repositories/NotificationRepository.h"
#include "../services/TenantService.h"
#include "../services/NotificationService.h"

#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
    Console(TenantService&, NotificationService&);
    void run();

private:
	int readInt(const std::string&);
	std::string readStr(const std::string&);
	void printTenant(const Tenant&, const std::string&);
	void printTenants(std::vector<Tenant>, const std::string&);
	void addTenant();
	void updateTenant();
	void deleteTenant();
	void showTenants();
	void findApartment();
	void filterApartments();
	void sortApartments();
	void addNotifiedApartment();
	void showNotifiedTenats();
	void deleteNotifiedApartments();
	void generateNotifiedApartments();
	void goodbye();
	void addTenants();
	int askOption();

    TenantService& service;
    NotificationService& notificationService;
};

#endif // CONSOLE_H
