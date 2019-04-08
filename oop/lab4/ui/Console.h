#include <string>
#include <vector>

#include "../entities/Tenant.h"
#include "../repositories/TenantRepository.h"
#include "../services/TenantService.h"

#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
public:
    Console(TenantService&);
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
	void goodbye();
	void addTenants();
	int askOption();

    TenantService& service;
};

#endif // CONSOLE_H
